# Bài tập 04: Thiết kế mô-đun tính cước GrabRide (Trip Fare Module)

## 1. Phân tích yêu cầu

### Đầu vào

| Tên biến | Kiểu C | Ý nghĩa | Miền hợp lệ |
|---|---|---|---|
| `distance_km` | `double` | Khoảng cách thực tế (km) | `distance_km > 0` |
| `is_surge` | `int` | Trời mưa hoặc giờ cao điểm | 0 hoặc 1 |

### Biến xử lý và kết quả (`double`)

`base_fare` (cước cơ bản), `surge_fee` (tiền phụ phí), `total_fare` (tổng thanh toán).

### Hằng số nghiệp vụ

| Hằng số | Giá trị |
|---|---|
| `opening_fare` | 12.000 VNĐ (giá mở cửa) |
| `opening_distance` | 2.0 km |
| `price_per_km` | 4.500 VNĐ/km |
| `surge_rate` | 0.2 (phụ phí 20% trên cước cơ bản) |

### Đầu ra

Hóa đơn hợp lệ:

```
========== HOA DON CHUYEN XE GRABRIDE ==========
Khoang cach          : 3.00 km
Trang thai           : Mua / Gio cao diem (+20%)
Cuoc co ban          : 16500.00 VND
Tien phu phi         : 3300.00 VND
------------------------------------------------
TONG CHI PHI THANH TOAN: 19800.00 VND
```

Dữ liệu sai: in một dòng `LOI: ... Tu choi xu ly.` rồi dừng, không in hóa đơn.

## 2. Luồng dữ liệu (Data Flow)

```
 Ban phim
    |  distance_km, is_surge
    v
+-------------------+   scanf that bai   +--------------------------+
| BUOC 1: NHAP      | -----------------> | LOI dinh dang -> DUNG    |
+-------------------+                    +--------------------------+
    |
    v
+-------------------+  distance_km <= 0  +--------------------------+
| BUOC 2: KIEM TRA  | -----------------> | LOI cu ly -> DUNG        |
| (tach rieng, khong|  is_surge != 0,1   +--------------------------+
|  tinh tien o day) | -----------------> | LOI phu phi -> DUNG      |
+-------------------+                    +--------------------------+
    |  du lieu sach
    v
+-------------------+
| BUOC 3: CUOC CO   |  distance_km <= 2.0 : base_fare = 12000
| BAN               |  distance_km >  2.0 : base_fare = 12000 + (km - 2.0) * 4500
+-------------------+
    |  base_fare
    v
+-------------------+
| BUOC 4: PHU PHI   |  is_surge == 1 : surge_fee = base_fare * 0.2
|                   |  nguoc lai     : surge_fee = 0
+-------------------+
    |  total_fare = base_fare + surge_fee
    v
+-------------------+
| BUOC 5: IN HOA DON|  base_fare, surge_fee, total_fare
+-------------------+
```

Dữ liệu chỉ đi qua tầng tính tiền khi đã vượt qua toàn bộ tầng kiểm tra.

## 3. Quyết định thiết kế

1. **Tách kiểm tra khỏi tính toán:** mọi kiểm tra nằm trước phép tính tiền. Sai thì `return 1` ngay, nên không thể có hóa đơn từ dữ liệu rác.
2. **Chỉ dùng `if` / `else` đơn:** không dùng `else if`, vòng lặp, hàm, mảng hay `struct`. Hai điều kiện của `is_surge` được gộp bằng `&&` (`is_surge != 0 && is_surge != 1`), không cần nhánh phụ.
3. **Kiểm tra giá trị trả về của `scanf`:** chặn trường hợp người dùng nhập chữ, tránh dùng biến chưa có giá trị.
4. **Điều kiện cự ly viết dạng phủ định** `!(distance_km > 0.0)`: chặn được cả 0, số âm và giá trị đặc biệt `nan`.
5. **Giá mở cửa 2 km đầu cố định:** nhánh `distance_km <= 2.0` gán thẳng 12.000, nên chuyến 0.3 km hay đúng 2.0 km đều không bị giảm giá theo tỉ lệ.
6. **Hằng số `const double`:** giá và hệ số khai báo một lần ở đầu chương trình, đổi giá chỉ sửa một chỗ.
7. **Tách `surge_fee` riêng:** hóa đơn hiển thị rõ ba dòng cước cơ bản, phụ phí và tổng, đáp ứng yêu cầu minh bạch.

## 4. Kiểm thử (đã chạy thực tế)

| # | distance_km | is_surge | Cước cơ bản | Phụ phí | Tổng | Kết quả |
|---|---|---|---|---|---|---|
| 1 | 1 | 0 | 12.000 | 0 | 12.000 | ✔ |
| 2 | 0.3 | 1 | 12.000 | 2.400 | 14.400 | ✔ |
| 3 | 2.0 | 0 | 12.000 | 0 | 12.000 (điểm biên) | ✔ |
| 4 | 2.0 | 1 | 12.000 | 2.400 | 14.400 | ✔ |
| 5 | 2.01 | 0 | 12.045 | 0 | 12.045 | ✔ |
| 6 | 3 | 0 | 16.500 | 0 | 16.500 | ✔ |
| 7 | 3 | 1 | 16.500 | 3.300 | 19.800 | ✔ |
| 8 | 10 | 1 | 48.000 | 9.600 | 57.600 | ✔ |
| 9 | 0 | 0 | | | Từ chối: cự ly không hợp lệ | ✔ |
| 10 | -5 | 0 | | | Từ chối: cự ly không hợp lệ | ✔ |
| 11 | 5 | 2 | | | Từ chối: phụ phí không hợp lệ | ✔ |
| 12 | 5 | -1 | | | Từ chối: phụ phí không hợp lệ | ✔ |
| 13 | `abc` | 0 | | | Từ chối: sai định dạng | ✔ |
| 14 | `nan` | 0 | | | Từ chối: cự ly không hợp lệ | ✔ |

## 5. Biên dịch và chạy

```bash
gcc -std=c11 -Wall -Wextra -pedantic -o main main.c
./main
```

Biên dịch không có lỗi hoặc cảnh báo.
