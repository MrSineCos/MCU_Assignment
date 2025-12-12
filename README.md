# Traffic Light Controller (STM32F103)

## Tổng quan
- Vi điều khiển: STM32F103C8 (HAL).
- Chức năng: điều khiển 2 hướng đèn giao thông (trục dọc & ngang), hiển thị trạng thái và thời gian đếm trên LCD I2C.
- Giao tiếp chính: I2C (LCD 16x2), UART debug (USART2), Timer2 (ngắt định kỳ cho software timer và quét phím).

## Kiến trúc & hành vi
- FSM chính:
  - **Automatic**: tuần tự R-G, R-Y, G-R, Y-R theo thời gian cấu hình.
  - **Manual**: chuyển bước thủ công, giữ an toàn theo cặp màu.
  - **Setting**: cho phép thiết lập thời gian Red / Yellow / Green; chỉ chấp nhận cấu hình hợp lệ (red = green + yellow, tất cả > 0).
- Bộ đếm & thời gian: dùng **software timer** chạy trong ngắt TIM2 (1 ms tick).
- Hiển thị:
  - LCD row 1: tên mode (AUTO / MANUAL / SET + trạng thái con).
  - LCD row 2: đếm thời gian dạng `V:xx   H:yy` (trục dọc & ngang) hoặc `TIME:xxs` khi chỉnh.
- Đèn tín hiệu: mỗi hướng điều khiển bằng 2 GPIO (mã hóa 2 bit: 00 off, 01 green, 10 yellow, 11 red).

## Điều khiển & nút nhấn
- Phím (đọc trong ngắt, có debounce):
  - MODE: chuyển AUTO ↔ MANUAL ↔ SET.
  - INC / DEC (tùy thiết kế): tăng/giảm thời gian khi ở SET; chuyển bước khi ở MANUAL.
  - SET/CONFIRM: lưu cấu hình nếu hợp lệ.

## Tệp nguồn chính
- `Core/Src/main.c`: khởi tạo HAL, clock, GPIO, I2C, UART, TIM2; vòng lặp chạy FSM.
- `Core/Src/fsm_automatic.c`, `fsm_manual.c`, `fsm_setting.c`: logic trạng thái.
- `Core/Src/software_timer.c`: timer mềm.
- `Core/Src/traffic_light.c`: điều khiển đèn theo mã màu 2 bit.
- `Core/Src/i2c_lcd.c`: driver LCD I2C 16x2.
- `Core/Src/button.c`: đọc phím, chống dội.

## Ghi chú build/flash
- Toolchain: STM32CubeIDE hoặc Make + arm-none-eabi-gcc.
- Ngắt TIM2 phải được bật (HAL_TIM_Base_Start_IT) và ưu tiên phù hợp.
- Kiểm tra địa chỉ I2C của LCD (thường 0x27 hoặc 0x3F) trong `i2c_lcd.c`.
