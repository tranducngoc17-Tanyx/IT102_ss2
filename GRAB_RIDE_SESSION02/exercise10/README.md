# Bài tập 03: Trade-off giữa if lồng nhau và Guard Clauses trong TripFareEngine

> Ghi chú: tiêu đề đề bài nhắc đến `if-else if` vs `switch-case`, nhưng phần yêu cầu kỹ thuật lại so sánh **if lồng nhiều tầng** với **Guard Clauses + tính theo bước**. Bài này làm theo phần yêu cầu kỹ thuật.

## 1. Phân tích bài toán (I/O)

### Đầu vào

| Tên biến | Kiểu C | Ý nghĩa | Miền hợp lệ |
|---|---|---|---|
| `distance_km` | `double` | Quãng đường (km) | `distance_km > 0` |
| `is_surge` | `int` | Phụ phí thời tiết xấu/cao điểm | 0 hoặc 1 |

### Đầu ra

- Hợp lệ: `Tong cuoc phi chuyen xe: <số> VND` (làm tròn 2 chữ số thập phân).
- Không hợp lệ: một dòng `LOI: ...` rồi dừng, không tính toán.

### Quy tắc nghiệp vụ

- `distance_km ≤ 2.0`: cước 12.000 VNĐ (đúng 2.0 km vẫn là 12.000, không cộng phụ trội).
- `distance_km > 2.0`: 12.000 + (distance_km − 2.0) × 4.500.
- `is_surge == 1`: nhân toàn bộ cước với 1.2.

## 2. Hai giải pháp

### Giải pháp 1: Legacy, if lồng nhiều tầng

```c
if (distance_km > 0.0) {
    if (is_surge == 0 || is_surge == 1) {
        if (distance_km <= 2.0) {
            if (is_surge == 1) {
                total_fare = 12000.0 * 1.2;
            } else {
                total_fare = 12000.0;
            }
        } else {
            if (is_surge == 1) {
                total_fare = (12000.0 + (distance_km - 2.0) * 4500.0) * 1.2;
            } else {
                total_fare = 12000.0 + (distance_km - 2.0) * 4500.0;
            }
        }
        printf("Tong cuoc phi chuyen xe: %.2f VND\n", total_fare);
    } else {
        printf("LOI: Trang thai phu phi khong hop le.\n");
    }
} else {
    printf("LOI: Quang duong khong hop le.\n");
}
```

Vấn đề:
- Lồng 4 tầng, phần xử lý lỗi bị đẩy xuống cuối và tách xa điều kiện gây ra nó (`else` của tầng ngoài cùng nằm cách điều kiện hàng chục dòng).
- Công thức phụ phí `* 1.2` lặp ở 2 nơi, công thức cước vượt 2 km lặp ở 2 nơi, số `12000.0` xuất hiện 4 lần.
- Muốn đổi 20% thành 25% phải sửa nhiều chỗ, chỉ cần sót một nhánh là hóa đơn sai.

### Giải pháp 2: Refactored, Guard Clauses + Step-by-Step

```c
/* Buoc 1: guard clauses, sai la thoat som */
if (!(distance_km > 0.0))            { /* bao loi */ return 1; }
if (is_surge != 0 && is_surge != 1)  { /* bao loi */ return 1; }

/* Buoc 2: cuoc co ban */
if (distance_km <= base_distance) {
    total_fare = base_fare;
} else {
    total_fare = base_fare + (distance_km - base_distance) * price_per_km;
}

/* Buoc 3: phu phi, chi viet mot lan */
if (is_surge == 1) {
    total_fare = total_fare * surge_multiplier;
}
```

Các giá trị 12000, 2.0, 4500, 1.2 được khai báo một lần bằng `const double` ở đầu chương trình.

## 3. Bảng so sánh

| Tiêu chí | Giải pháp 1 (lồng nhau) | Giải pháp 2 (Guard Clauses) |
|---|---|---|
| Độ phức tạp đọc hiểu | Cao: 4 tầng lồng, phải theo dõi nhiều điều kiện cùng lúc | Thấp: đọc từ trên xuống, mỗi bước một việc |
| Khả năng bảo trì khi đổi giá | Kém: sửa 2 đến 4 chỗ, dễ sót | Tốt: sửa 1 hằng số |
| Trùng lặp mã nguồn | Có: công thức phụ phí và cước vượt 2 km lặp lại | Không: mỗi công thức chỉ viết một lần |
| Khả năng mở rộng | Kém: thêm một loại phụ phí thì số nhánh nhân đôi (2 × 2 × ...) | Tốt: thêm một bước tính hoặc một guard mới, các bước cũ giữ nguyên |
| Xử lý dữ liệu lỗi | Nằm rải rác, xa điều kiện gây lỗi | Nằm gọn ở đầu, lỗi là thoát ngay |

Với hai điều kiện đầu vào, số nhánh tính tiền của giải pháp 1 là 2 × 2 = 4. Mỗi yếu tố mới (ví dụ phí đêm) nhân đôi số nhánh, còn giải pháp 2 chỉ thêm một bước.

## 4. Quyết định lựa chọn

**Chọn giải pháp 2.** Lý do kỹ thuật:

1. **Nguyên tắc DRY:** mỗi quy tắc nghiệp vụ nằm đúng một nơi, nên đổi quy tắc chỉ sửa một nơi.
2. **Tách bạch trách nhiệm:** kiểm tra dữ liệu, tính cước cơ bản và tính phụ phí là ba bước độc lập, có thể đọc và kiểm thử riêng.
3. **Thoát sớm:** dữ liệu sai bị chặn trước khi chạm đến logic tiền tệ, phù hợp yêu cầu của hệ thống thanh toán.
4. **Kết quả tương đương:** đã đối chiếu hai phiên bản trên cùng bộ dữ liệu hợp lệ, cho kết quả giống hệt nhau, nên việc tái cấu trúc không đổi hành vi.

Đánh đổi: giải pháp 2 dài hơn vài dòng khai báo hằng số. Đây là chi phí nhỏ so với lợi ích bảo trì.

## 5. Pseudocode của giải pháp đã chọn

```
BAT DAU
  Khai bao hang so: base_fare=12000, base_distance=2.0,
                    price_per_km=4500, surge_multiplier=1.2
  Nhap distance_km;  neu scanf that bai   -> LOI dinh dang, KET THUC
  Nhap is_surge;     neu scanf that bai   -> LOI dinh dang, KET THUC

  // Buoc 1: Guard Clauses
  NEU KHONG (distance_km > 0)             -> LOI quang duong, KET THUC
  NEU is_surge khac 0 VA khac 1           -> LOI phu phi, KET THUC

  // Buoc 2: Cuoc co ban
  NEU distance_km <= base_distance
      total_fare = base_fare
  NGUOC LAI
      total_fare = base_fare + (distance_km - base_distance) * price_per_km

  // Buoc 3: Phu phi
  NEU is_surge = 1
      total_fare = total_fare * surge_multiplier

  In total_fare (2 chu so thap phan)
KET THUC
```

## 6. Kiểm thử (đã chạy thực tế)

| # | distance_km | is_surge | Kết quả mong đợi | Kết quả chạy |
|---|---|---|---|---|
| 1 | 1 | 0 | 12.000 | 12000.00 ✔ |
| 2 | 0.5 | 1 | 12.000 × 1.2 = 14.400 | 14400.00 ✔ |
| 3 | 2.0 | 0 | 12.000 (điểm biên, không phụ trội) | 12000.00 ✔ |
| 4 | 2.0 | 1 | 14.400 | 14400.00 ✔ |
| 5 | 2.01 | 0 | 12.000 + 0.01 × 4.500 = 12.045 | 12045.00 ✔ |
| 6 | 3 | 0 | 16.500 | 16500.00 ✔ |
| 7 | 3 | 1 | 19.800 | 19800.00 ✔ |
| 8 | 10 | 1 | (12.000 + 36.000) × 1.2 = 57.600 | 57600.00 ✔ |
| 9 | 0 | 0 | Lỗi quãng đường | Báo lỗi ✔ |
| 10 | -5.0 | 0 | Lỗi quãng đường | Báo lỗi ✔ |
| 11 | 5 | 2 | Lỗi phụ phí | Báo lỗi ✔ |
| 12 | 5 | -1 | Lỗi phụ phí | Báo lỗi ✔ |
| 13 | 5 | 99 | Lỗi phụ phí | Báo lỗi ✔ |
| 14 | `abc` | 0 | Lỗi định dạng | Báo lỗi ✔ |
| 15 | `nan` | 0 | Lỗi quãng đường | Báo lỗi ✔ |

Trường hợp 14 cho thấy điểm yếu của bản legacy: nếu `scanf` không được kiểm tra, biến giữ giá trị rác và chương trình vẫn in ra một mức cước. Bản mới kiểm tra giá trị trả về của `scanf` nên chặn được.

## 7. Biên dịch và chạy

```bash
gcc -std=c11 -Wall -Wextra -pedantic -o main main.c
./main
```
