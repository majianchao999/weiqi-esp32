# Weiqi（维奇）板

基于 `78/xiaozhi-esp32` 的基础板框架，不包含任何 OttoRobot 舵机/动作代码。

## 硬件接口（固件配置）

以下为固件需要的引脚/接口配置：

- 麦克风 I2S：WS = GPIO4，SCK = GPIO5，DIN = GPIO6
- 扬声器 I2S：BCLK = GPIO15，LRCK = GPIO16，DIN = GPIO7
- BOOT 按键：GPIO0
- 屏幕：当前无屏；固件预留 ST7789 240x240（引脚见 `config.h`）

## 编译

```bash
idf.py set-target esp32s3
idf.py menuconfig
# Board Type -> Weiqi (维奇)
# Weiqi Display -> No display（默认）/ ST7789 240x240
idf.py build
```

默认无屏构建；接屏后选择 `CONFIG_WEIQI_DISPLAY_ST7789_240X240` 并核对
`config.h` 里的显示引脚。

## 音频/AEC

- 输入/输出 16 kHz
- `NoAudioCodecSimplex` 使用 `input_reference=true`：没有硬件回采时由
  `NoAudioCodec` 缓存播放 PCM 作为 AFE 的软件参考，启用 AEC。
- 唤醒词使用 WakeNet `wn9_nihaoxiaozhi_tts`（与基础固件一致）。

## License

软件部分基于 MIT（见仓库根目录 `LICENSE`），保留原版权声明；本项目基于
`78/xiaozhi-esp32`。
