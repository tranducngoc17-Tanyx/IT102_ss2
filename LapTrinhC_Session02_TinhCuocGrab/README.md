# Bài tập 05: Hệ thống tính cước GrabRide (demo trên lớp)

## 1. Phân tích bài toán

### Đầu vào

| Tên biến | Kiểu C | Ý nghĩa | Miền hợp lệ |
|---|---|---|---|
| `distance` | `float` | Quãng đường thực tế (km) | `distance > 0` |
| `has_promo` | `int` | Có mã giảm giá 20% hay không | 0 hoặc 1 |

Biến kết quả: `total_fare` (`double`, để tránh mất chính xác khi nhân tiền).

### Hằng số nghiệp vụ

| Hằng số | Giá trị |
|---|---|
| `price_per_km` | 20.000 VNĐ/km |
| `promo_rate` | 0.8 (giảm 20%) |
| `minimum_fare` | 15.000 VNĐ (cước sàn) |

### Đầu ra

- Hợp lệ: `Tong cuoc phi: [số tiền] VNĐ` (làm tròn 2 chữ số thập phân).
- Không hợp lệ: `Loi: Du lieu dau vao khong hop le!`

## 2. Thuật toán

```
BAT DAU
  Nhap distance, has_promo
  NEU scanf that bai HOAC distance khong > 0 HOAC has_promo khac 0 va khac 1
      In "Loi: Du lieu dau vao khong hop le!" -> KET THUC

  total_fare = distance * 20000
  NEU has_promo = 1
      total_fare = total_fare * 0.8
  NEU total_fare < 15000
      total_fare = 15000

  In "Tong cuoc phi: total_fare VNĐ"
KET THUC
```

Thứ tự bắt buộc: kiểm tra dữ liệu, tính cước gốc, giảm giá, rồi mới áp cước sàn. Cước sàn phải áp **sau cùng** vì đề quy định giá sàn tính trên cước sau giảm.

## 3. Quyết định thiết kế

1. **Kiểm tra trước, tính sau:** dữ liệu sai bị chặn bằng `return 1` trước mọi phép tính.
2. **Kiểm tra `scanf`:** nếu người dùng nhập chữ, chương trình báo lỗi thay vì dùng biến chưa có giá trị.
3. **Điều kiện `!(distance > 0.0f)`:** chặn được 0, số âm và giá trị đặc biệt `nan`.
4. **Dùng `double` cho tiền:** `distance` là `float` theo đề, nhưng khi nhân với 20.000 kết quả được lưu vào `double` để giữ độ chính xác.
5. **Hằng số `const`:** đổi đơn giá, mức giảm hoặc cước sàn chỉ sửa một chỗ.

## 4. Giả định cần lưu ý

Đề nêu "tổng cước phí sau khi giảm giá không được thấp hơn 15.000 VNĐ" và mục đích là "đảm bảo chi phí tối thiểu cho tài xế". Bài này hiểu cước sàn áp dụng cho **mọi chuyến đi**, kể cả khi không có mã giảm giá. Ví dụ chuyến 0.5 km không có mã: 0.5 × 20.000 = 10.000, được nâng lên 15.000. Nếu giáo viên chỉ muốn áp cước sàn khi có mã giảm giá, chỉ cần đưa khối `if (total_fare < minimum_fare)` vào bên trong khối `if (has_promo == 1)`.

## 5. Kiểm thử (đã chạy thực tế)

### Năm trường hợp của đề

| Case | distance | has_promo | Kết quả kỳ vọng | Kết quả chạy |
|---|---|---|---|---|
| 1 | 5.0 | 0 | Tong cuoc phi: 100000.00 VNĐ | Đúng ✔ |
| 2 | 10.0 | 1 | Tong cuoc phi: 160000.00 VNĐ | Đúng ✔ |
| 3 | 0.8 | 1 | Tong cuoc phi: 15000.00 VNĐ (cước sàn) | Đúng ✔ |
| 4 | -2.5 | 0 | Loi: Du lieu dau vao khong hop le! | Đúng ✔ |
| 5 | 3.0 | 5 | Loi: Du lieu dau vao khong hop le! | Đúng ✔ |

### Trường hợp bổ sung

| distance | has_promo | Kết quả | Ghi chú |
|---|---|---|---|
| 0.5 | 0 | 15000.00 | Cước sàn áp dụng khi không có mã (xem mục 4) |
| 0.9375 | 1 | 15000.00 | Đúng điểm biên: 18.750 × 0.8 = 15.000 |
| 1 | 1 | 16000.00 | Trên sàn: 20.000 × 0.8 |
| 0 | 0 | Báo lỗi | distance bằng 0 |
| 3 | -1 | Báo lỗi | has_promo âm |
| `abc` | 0 | Báo lỗi | Sai định dạng |
| `nan` | 0 | Báo lỗi | Giá trị đặc biệt |
| 5 | `x` | Báo lỗi | has_promo sai định dạng |

## 6. Biên dịch và chạy

```bash
gcc -std=c11 -Wall -Wextra -pedantic -o main main.c
./main
```

Biên dịch không có lỗi hoặc cảnh báo.

Lưu ý: chuỗi `VNĐ` chứa chữ `Đ`, nên tệp `main.c` cần lưu ở dạng UTF-8. Trên Windows, nếu terminal hiển thị sai chữ `Đ`, chạy `chcp 65001` trước khi chạy chương trình.
