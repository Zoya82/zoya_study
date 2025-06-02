from pydub import AudioSegment

# 加载音频
audio = AudioSegment.from_wav("audio.wav")

# 剪切(前5秒)
first_5_sec = audio[:5000]  # 毫秒为单位

# 格式转换
audio.export("output.mp3", format="mp3")




import librosa
import librosa.display

# 加载音频
y, sr = librosa.load("audio.wav")

# 显示频谱图
plt.figure(figsize=(12, 4))
librosa.display.waveshow(y, sr=sr)
plt.title('Waveform (librosa)')
plt.show()