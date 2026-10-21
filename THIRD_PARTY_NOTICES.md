# Third-Party Notices / 第三方组件说明

This repository's own code is licensed under the **MIT License** (see
[`LICENSE`](LICENSE)). The project is based on
[78/xiaozhi-esp32](https://github.com/78/xiaozhi-esp32) (MIT); the original
copyright notices are retained.

The firmware uses third-party components that are fetched at build time by the
ESP-IDF Component Manager (see [`main/idf_component.yml`](main/idf_component.yml)).
Those components are governed by their own licenses, which apply in addition to
this repository's MIT license:

| Component | License / terms |
|---|---|
| ESP-IDF | Apache-2.0 — https://github.com/espressif/esp-idf |
| ESP-SR (WakeNet / MultiNet speech models) | Espressif ESP-SR license; model usage, including commercial use, is subject to Espressif's terms — https://github.com/espressif/esp-sr |
| LVGL | MIT — https://lvgl.io; GIF decoder notice: `main/display/lvgl_display/gif/LICENSE.txt` |
| 78/xiaozhi-fonts | See the component's license in its repository/package |
| Other components in `main/idf_component.yml` | See each component's `LICENSE`/`README` under `managed_components/` after a build |

The board/third-party source code retained from the upstream repository remains
under the upstream MIT license; original copyright notices are preserved.
