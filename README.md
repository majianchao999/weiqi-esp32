# Weiqi（维奇）ESP32-S3 语音助手固件

本仓库是 **维奇（Weiqi）** 板的 ESP32-S3 固件源代码，基于
[78/xiaozhi-esp32](https://github.com/78/xiaozhi-esp32) 开发，软件采用 **MIT** 许可证。

> 本仓库包含固件源代码与板级配置；上游项目的完整说明保留在
> [`README_UPSTREAM.md`](README_UPSTREAM.md)，中文/日文版本为
> [`README_zh.md`](README_zh.md) / [`README_ja.md`](README_ja.md)。

## 硬件接口

以下是固件使用的板级接口（详细引脚与可选项见
[`main/boards/weiqi/README.md`](main/boards/weiqi/README.md)）：

| 功能 | GPIO / 参数 |
|---|---|
| 麦克风 INMP441（I2S） | WS = GPIO4，SCK = GPIO5，DIN = GPIO6 |
| 扬声器 MAX98357（I2S） | BCLK = GPIO15，LRCK = GPIO16，DIN = GPIO7 |
| BOOT 按键 | GPIO0 |
| 屏幕 | 默认无屏；可选 ST7789 240×240（引脚见 `main/boards/weiqi/config.h`） |

## 功能

- ESP32-S3-WROOM-1-N16R8，8 MB PSRAM
- 麦克风 + 功放，16 kHz 音频链路
- **软件回采 AEC**：`NoAudioCodec` 缓存播放 PCM 作为 AFE 参考，配合
  AFE `AEC(FD_LOW_COST)` 做回声消除
- 本地唤醒词：WakeNet `wn9_nihaoxiaozhi_tts`（“你好小智”）
- 无屏默认构建；可选 ST7789 240×240 LVGL 显示
- OTA 升级（默认 OTA 地址可在 menuconfig 中修改）
- 支持配套服务端的通知/音乐推送

## 编译

需要 ESP-IDF v6.1：

```bash
idf.py set-target esp32s3
idf.py menuconfig
#   Target Board -> Weiqi (维奇)
#   Weiqi Display -> No display (默认) / ST7789 240x240
idf.py build
```

Windows 下也可以使用仓库内的 `build_fw.bat build`。

## 烧录

```bash
idf.py -p COMx flash
```

OTA 升级由配套服务端提供；OTA URL 在 `menuconfig` 的 `OTA_URL` 中配置。

## 目录

- `main/boards/weiqi/` — 维奇板配置、音频/显示和构建说明
- `main/` — 固件源码
- `README_UPSTREAM.md` — 上游 78/xiaozhi-esp32 原始说明（保留）
- `THIRD_PARTY_NOTICES.md` — 第三方组件许可证说明

## 许可证与来源

- 本项目软件：**MIT**，见根目录 [`LICENSE`](LICENSE)；保留上游版权声明。
- 基于 [78/xiaozhi-esp32](https://github.com/78/xiaozhi-esp32)（MIT）。
- 第三方组件（ESP-IDF、ESP-SR/WakeNet、LVGL、字体等）的许可证见
  [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md)。

MIT 允许修改、再分发和商用，只需保留版权与许可声明；无需合并回上游。
