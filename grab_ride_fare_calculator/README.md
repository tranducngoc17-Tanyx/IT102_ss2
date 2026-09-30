# Bài tập 02: Phân hệ tính cước chuyến xe GrabRide đa yếu tố

## 1. Phân tích bài toán (I/O)

### Đầu vào

| Tên biến | Kiểu C | Ý nghĩa | Miền hợp lệ |
|---|---|---|---|
| `vehicle_type` | `int` | Mã dịch vụ | 1 = GrabBike, 2 = GrabCar |
| `distance` | `double` | Khoảng cách (km) | 0 < distance ≤ 300 |
| `is_peak_or_rain` | `int` | Phụ phí cao điểm/mưa | 0 = bình thường, 1 = có phụ phí |

Các biến trung gian và kết quả (`double`): `base_fare`, `surcharge`, `total_fare`.

### Đầu ra

Hóa đơn hợp lệ:

```
===== HOA DON CHUYEN XE GRABRIDE =====
Dich vu        : GrabBike
Khoang cach    : 5.00 km
Cuoc co so     : 25500 VND
Phu phi        : 5100 VND
Tong thanh toan: 30600 VND
```

Dữ liệu sai: in một dòng `LOI: ...` nêu lý do, hủy hóa đơn và thoát chương trình với mã 1.

### Bảng giá

| Dịch vụ | 2 km đầu (≤ 2.0 km) | Mỗi km vượt quá 2 km |
|---|---|---|
| GrabBike | 12.000 VNĐ (giá cố định) | 4.500 VNĐ/km |
| GrabCar | 25.000 VNĐ (giá cố định) | 10.000 VNĐ/km |

Phụ phí = 20% cước cơ sở khi `is_peak_or_rain == 1`, ngược lại bằng 0.
Tổng cước = cước cơ sở + phụ phí.

## 2. Đề xuất giải pháp

Nguyên tắc chính: **kiểm tra toàn bộ dữ liệu trước, tính tiền sau**. Phép tính tài chính chỉ chạy khi mọi dữ liệu đã hợp lệ.

1. **Sai định dạng:** kiểm tra giá trị trả về của `scanf` (phải bằng 1). Nếu người dùng nhập chữ, chương trình báo lỗi thay vì dùng biến chưa có giá trị.
2. **Mã xe / phụ phí không hợp lệ:** dùng `!=` kết hợp `&&` (`vehicle_type != 1 && vehicle_type != 2`), nên mọi giá trị ngoài tập hợp lệ (âm, 3, 5, 99...) đều bị chặn.
3. **Cự ly bất thường:** điều kiện hợp lệ viết dạng phủ định `!(distance > 0.0 && distance <= 300.0)`. Cách viết này còn chặn được giá trị đặc biệt `nan`, vì mọi phép so sánh với `nan` đều sai.
4. **Ngưỡng 2 km đầu:** dùng nhánh `if (distance <= 2.0)` gán thẳng giá cố định, không nhân theo tỉ lệ km, nên chuyến 0.3 km hay 1.8 km đều trả đúng giá sàn.
5. **Phân loại xe:** `if (vehicle_type == 1) ... else ...` lồng nhánh khoảng cách. Vì mã xe đã được kiểm tra ở bước trước, nhánh `else` chỉ có thể là GrabCar.
6. **Phụ phí:** tính riêng `surcharge = base_fare * 0.2`, để hóa đơn hiển thị rõ ba dòng: cước cơ sở, phụ phí, tổng.

## 3. Các bước xử lý (pseudocode)

```
BAT DAU
  Nhap vehicle_type;   neu scanf that bai      -> LOI dinh dang, KET THUC
  Nhap distance;       neu scanf that bai      -> LOI dinh dang, KET THUC
  Nhap is_peak_or_rain; neu scanf that bai     -> LOI dinh dang, KET THUC

  NEU vehicle_type khac 1 VA khac 2            -> LOI ma xe, KET THUC
  NEU is_peak_or_rain khac 0 VA khac 1         -> LOI phu phi, KET THUC
  NEU KHONG (0 < distance <= 300)              -> LOI cu ly, KET THUC

  NEU vehicle_type = 1 (GrabBike)
      NEU distance <= 2.0  THI base_fare = 12000
      NGUOC LAI            base_fare = 12000 + (distance - 2.0) * 4500
  NGUOC LAI (GrabCar)
      NEU distance <= 2.0  THI base_fare = 25000
      NGUOC LAI            base_fare = 25000 + (distance - 2.0) * 10000

  NEU is_peak_or_rain = 1 THI surcharge = base_fare * 0.2
  NGUOC LAI                   surcharge = 0

  total_fare = base_fare + surcharge
  In hoa don
KET THUC
```

## 4. Bảng test case (đã chạy thực tế)

### Nhóm hợp lệ

| # | vehicle_type | distance | is_peak_or_rain | Kết quả mong đợi | Kết quả chạy |
|---|---|---|---|---|---|
| 1 | 1 | 0.3 | 0 | 12.000 (giá sàn) | 12000 ✔ |
| 2 | 1 | 1.8 | 0 | 12.000 (giá sàn) | 12000 ✔ |
| 3 | 1 | 2.0 | 0 | 12.000 (đúng ngưỡng) | 12000 ✔ |
| 4 | 1 | 5 | 0 | 12.000 + 3 × 4.500 = 25.500 | 25500 ✔ |
| 5 | 1 | 5 | 1 | 25.500 × 1.2 = 30.600 | 30600 ✔ |
| 6 | 2 | 1.5 | 0 | 25.000 (giá sàn) | 25000 ✔ |
| 7 | 2 | 2.5 | 0 | 25.000 + 0.5 × 10.000 = 30.000 | 30000 ✔ |
| 8 | 2 | 10 | 1 | (25.000 + 80.000) × 1.2 = 126.000 | 126000 ✔ |
| 9 | 1 | 300 | 0 | 12.000 + 298 × 4.500 = 1.353.000 (biên trên) | 1353000 ✔ |

### Nhóm dữ liệu lỗi

| # | Dữ liệu nhập | Lý do | Kết quả |
|---|---|---|---|
| 10 | `1 300.1 0` | Vượt 300 km | Báo lỗi cự ly ✔ |
| 11 | `1 0 0` | distance = 0 | Báo lỗi cự ly ✔ |
| 12 | `1 -5 0` | distance âm | Báo lỗi cự ly ✔ |
| 13 | `3 5 0` | Mã xe = 3 | Báo lỗi mã xe ✔ |
| 14 | `0 5 0` | Mã xe = 0 | Báo lỗi mã xe ✔ |
| 15 | `1 5 2` | Phụ phí = 2 | Báo lỗi phụ phí ✔ |
| 16 | `1 5 -1` | Phụ phí âm | Báo lỗi phụ phí ✔ |
| 17 | `abc 5 0` | Mã xe sai định dạng | Báo lỗi định dạng ✔ |
| 18 | `1 xyz 0` | Khoảng cách sai định dạng | Báo lỗi định dạng ✔ |
| 19 | `1 nan 0` | Giá trị đặc biệt `nan` | Báo lỗi cự ly ✔ |

## 5. Biên dịch và chạy

```bash
gcc -std=c11 -Wall -Wextra -pedantic -o main main.c
./main
```

Biên dịch không có cảnh báo.

## 6. Hạn chế đã biết

Nếu nhập số thực cho ô số nguyên (ví dụ mã xe `1.5`), `scanf("%d")` chỉ đọc phần `1` và để lại `.5` cho lần đọc tiếp theo. Việc xử lý triệt để cần đọc cả dòng bằng chuỗi, thuộc kiến thức nâng cao chưa nằm trong phạm vi bài này.
