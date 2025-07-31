import os
from flask import Flask, render_template, request, redirect, url_for, session, flash
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager, UserMixin, login_user, login_required, logout_user, current_user
from werkzeug.security import generate_password_hash, check_password_hash
from werkzeug.utils import secure_filename
from sqlalchemy.exc import IntegrityError
import hashlib
from datetime import datetime

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # 用于会话管理
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///mv.db'  # 使用朋友的 mv.db
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True
app.config['SQLALCHEMY_ECHO'] = True
app.config['UPLOAD_FOLDER'] = 'static/upload/video'  # 朋友的视频上传路径
app.config['ALLOWED_EXTENSIONS'] = {'png', 'jpg', 'jpeg', 'gif', 'mp4'}  # 允许的文件扩展名
db = SQLAlchemy(app)
login_manager = LoginManager()
login_manager.init_app(app)

# 创建上传目录
if not os.path.exists(app.config['UPLOAD_FOLDER']):
    os.makedirs(app.config['UPLOAD_FOLDER'])

# 用户模型（你的代码）
class User(UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password_hash = db.Column(db.String(120), nullable=False)
    avatar = db.Column(db.String(120), nullable=True)  # 用户头像路径

    # 多对多关系：用户和视频的观看历史
    watched_movies = db.relationship(
        'MovieORM',  # 关联到 MovieORM 模型
        secondary='user_movie_association',  # 通过中间表关联
        backref=db.backref('viewers', lazy='dynamic'),  # 反向引用，表示视频的观看者
        lazy='dynamic'  # 动态加载，允许灵活查询
    )

    def set_password(self, password):
        self.password_hash = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)

    def add_to_history(self, movie):
        """将视频添加到用户的观看历史"""
        if movie not in self.watched_movies:
            self.watched_movies.append(movie)
            db.session.commit()

    def get_history(self):
        """获取用户的观看历史"""
        return self.watched_movies.all()

user_movie_association = db.Table(
    'user_movie_association',
    db.Column('user_id', db.Integer, db.ForeignKey('user.id'), primary_key=True),
    db.Column('movie_id', db.Integer, db.ForeignKey('movie.id'), primary_key=True)
)

# 视频模型（朋友的代码）
class MovieORM(db.Model):
    __tablename__ = 'movie'
    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    name = db.Column(db.String(255), nullable=False)
    url = db.Column(db.String(255), nullable=False)
    create_at = db.Column(db.DateTime, default=datetime.now)
    status = db.Column(db.String(20), default='pending')  # 审核状态：pending, approved, rejected

# 初始化数据库
def create_tables():
    db.create_all()

# 加载用户
@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))

# 检查数据库是否已经初始化
@app.before_request
def check_and_create_tables():
    if not app.config.get('tables_created', False):
        create_tables()
        app.config['tables_created'] = True

# 用户主页（你的代码）
@app.route('/user', methods=['GET', 'POST'])
def user_profile():
    # 检查用户是否已登录
    if not current_user.is_authenticated:
        flash('你需要先登录!', 'danger')
        return redirect(url_for('login'))  # 重定向到登录页面

    # 如果用户已登录，继续处理用户主页逻辑
    if request.method == 'POST':
        if 'new_username' in request.form:
            new_username = request.form['new_username']
            current_user.username = new_username
            db.session.commit()
        elif 'new_password' in request.form:
            new_password = request.form['new_password']
            current_user.set_password(new_password)
            db.session.commit()
        elif 'video_title' in request.form:
            video_title = request.form['video_title']
            # 根据视频名称查找视频
            movie = MovieORM.query.filter_by(name=video_title).first()
            if movie:
                # 添加到用户的观看历史
                current_user.add_to_history(movie)
                flash('Video added to history!', 'success')
            else:
                flash('Video not found!', 'danger')
        elif 'avatar' in request.files:
            file = request.files['avatar']
            if file and allowed_file(file.filename):
                filename = secure_filename(file.filename)
                file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
                current_user.avatar = filename
                db.session.commit()
                flash('Avatar updated successfully!', 'success')
            else:
                flash('Invalid file type!', 'danger')

    # 获取用户的观看历史
    history = current_user.get_history()
    return render_template('user_profile.html', user=current_user, history=history)
# 注册页面（你的代码）
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        avatar = request.files['avatar']

        # 验证密码长度
        if len(password) < 6:
            flash('Password must be at least 6 characters long.', 'danger')
            return render_template('register.html')

        if avatar and allowed_file(avatar.filename):
            filename = secure_filename(avatar.filename)
            avatar.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        else:
            filename = None

        new_user = User(username=username, avatar=filename)
        new_user.set_password(password)
        db.session.add(new_user)

        try:
            db.session.commit()
            return redirect(url_for('login'))
        except IntegrityError:
            db.session.rollback()  # 回滚事务
            flash('Username already exists. Please choose a different username.', 'danger')
            return render_template('register.html')

    return render_template('register.html')
#历史回看
@app.route('/play/<int:movie_id>')
@login_required
def play_video(movie_id):
    # 根据 movie_id 查找视频
    movie = MovieORM.query.get_or_404(movie_id)
    # 渲染视频播放页面，传递视频的 URL

    return render_template('video_view.html', url=movie.url)

# 登录页面（你的代码）
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        if 'username' in request.form and 'password' in request.form:
            username = request.form['username']
            password = request.form['password']
            user = User.query.filter_by(username=username).first()
            if user and user.check_password(password):
                login_user(user)
                return redirect(url_for('video_list'))  # 登录后重定向到视频列表页面
            else:
                flash('Invalid username or password', 'danger')
        elif 'register' in request.form:
            return redirect(url_for('register'))
    return render_template('login.html')

# 注销页面（你的代码）
@app.route('/logout')
@login_required
def logout():
    logout_user()
    return redirect(url_for('login'))

#视频列表页面（朋友的代码）
@app.route('/')
def video_list():
    # 只显示审核通过的视频
    movie_list = MovieORM.query.filter_by(status='approved').all()

    # 检查用户是否已登录
    if current_user.is_authenticated:
        return render_template("video.html", movie_list=movie_list, user=current_user)
    else:
        flash('登录享受完整服务!', 'danger')
        return render_template("video.html", movie_list=movie_list)

# 视频播放页面（朋友的代码）
@app.route('/video_view')
def video_view():
    url = request.args.get('url')
    return render_template("video_view.html", url=url)

# 视频上传页面（朋友的代码）
@app.get("/upload_movie")
def upload_video():
    return render_template('video_upload.html')

# 视频上传处理（朋友的代码）
@app.post('/video_upload')
def upload_video2():
    file = request.files['file']
    if file:
        filename = file.filename
        content = file.read()
        name = hashlib.md5(content).hexdigest()
        suffix = os.path.splitext(filename)[-1]
        new_filename = name + suffix
        new_path = os.path.join(app.config['UPLOAD_FOLDER'], new_filename)
        open(new_path, mode='wb').write(content)

        mv = MovieORM()
        mv.url = '/' + new_path
        mv.name = filename
        mv.status = 'pending'  # 设置视频状态为待审核
        db.session.add(mv)
        db.session.commit()
    return {'code': 0, 'msg': '上传视频成功'}

# 管理员登录页面
@app.route('/admin_login', methods=['GET', 'POST'])
def admin_login():
    if request.method == 'POST':
        password = request.form.get('password')
        if password == '54321':  # 预设的管理员密码
            session['admin'] = True  # 在会话中标记为管理员
            return redirect(url_for('review_list'))
        else:
            flash('您没有管理员权限', 'danger')
    return render_template('admin_login.html')


# 管理员界面
@app.route('/admin/review_list')
def review_list():
    if not session.get('admin'):
        flash('您没有管理员权限', 'danger')
        return redirect(url_for('admin_login'))

    # 显示所有视频，包括已审核和未审核的
    videos = MovieORM.query.all()
    return render_template('review_list.html', videos=videos)

# 视频审核界面
@app.route('/admin/review_video/<int:video_id>', methods=['GET', 'POST'])
def review_video(video_id):
    if not session.get('admin'):
        flash('您没有管理员权限', 'danger')
        return redirect(url_for('admin_login'))

    video = MovieORM.query.get_or_404(video_id)

    if request.method == 'POST':
        action = request.form.get('action')
        if action == 'approve':
            video.status = 'approved'
            flash('视频审核通过', 'success')
        elif action == 'reject':
            video.status = 'rejected'
            flash('视频审核不通过', 'danger')
        elif action == 'pending':
            video.status = 'pending'
            flash('视频状态重置为待审核', 'info')
        elif action == 'delete':
            # 删除视频文件
            video_path = video.url.lstrip('/')
            if os.path.exists(video_path):
                os.remove(video_path)
            # 从数据库中删除记录
            db.session.delete(video)
            db.session.commit()
            flash('视频已删除', 'danger')

            # 返回主页
            return redirect(url_for('video_list'))  # 删除后直接跳转回主页

        db.session.commit()

    return render_template('review_video.html', video=video)

# 检查文件扩展名是否允许
def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in app.config['ALLOWED_EXTENSIONS']
# 模拟商户数据（你可以替换为数据库中的用户）
MERCHANTS = [
    {"id": 1, "name": "商户A"},
    {"id": 2, "name": "商户B"},
    {"id": 3, "name": "商户C"},
]

# 简单留言存储（可扩展为数据库模型）
MESSAGES = {
    1: [],
    2: [],
    3: []
}

@app.route('/communicate')
@login_required
def communicate():
    return render_template('communicate.html', merchants=MERCHANTS)

@app.route('/chat/<int:merchant_id>', methods=['GET', 'POST'])
@login_required
def chat(merchant_id):
    merchant = next((m for m in MERCHANTS if m['id'] == merchant_id), None)
    if not merchant:
        flash("找不到该商户", "danger")
        return redirect(url_for('communicate'))

    if request.method == 'POST':
        msg = request.form.get('message')
        if msg:
            MESSAGES[merchant_id].append(f"{current_user.username}: {msg}")
        return redirect(url_for('chat', merchant_id=merchant_id))

    return render_template('chat.html', merchant=merchant, messages=MESSAGES[merchant_id])
if __name__ == '__main__':
    app.run(debug=True,host='0.0.0.0',port=5000)
