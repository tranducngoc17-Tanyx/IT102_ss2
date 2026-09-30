# Bài tập 01: Dò luồng và sửa lỗi tính cước GrabRide

## 1. Phân tích lỗi

### Lỗi 1: Sai công thức cước cho quãng đường > 2 km (lỗi logic)

```c
} else {
    total_fare = distance * 4500.0;   // SAI
}
```

- **Nguyên nhân:** Code tính toàn bộ quãng đường theo 4.500 VNĐ/km, bỏ qua khoản cước cố định 12.000 VNĐ cho 2 km đầu và không trừ 2 km đầu ra khỏi phần tính theo km.
- **Công thức đúng:** `total_fare = 12000.0 + (distance - 2.0) * 4500.0;`
- **Kiểm chứng với khiếu nại:** 3 km cho ra 3 × 4.500 = 13.500 VNĐ (sai), trong khi đúng là 12.000 + (3 − 2) × 4.500 = 16.500 VNĐ.

### Lỗi 2: Dùng toán tử gán `=` thay cho toán tử so sánh `==`

```c
if (is_raining = 1) {   // SAI
```

- **Nguyên nhân:** `is_raining = 1` là phép gán. Nó gán 1 vào `is_raining` và giá trị biểu thức là 1 (khác 0) nên điều kiện luôn đúng. Vì vậy phụ phí 20% luôn được cộng dù người dùng nhập `0`. GCC vẫn biên dịch được vì phép gán trong điều kiện hợp lệ về cú pháp (chỉ cảnh báo khi dùng `-Wall`).
- **Cách sửa:** `if (is_raining == 1)`.

## 2. Bảng Test Cases đối chứng

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế | Kết quả đúng mong đợi |
|---|---|---|---|
| TC1: Chuyến dài > 2 km, trời nắng | `distance = 3`, `is_raining = 0` | 3 × 4.500 = 13.500, rồi × 1.2 do lỗi gán, ra **16.200 VND** | 12.000 + 1 × 4.500 = **16.500 VND** |
| TC2: Chuyến ngắn ≤ 2 km, trời nắng | `distance = 1.5`, `is_raining = 0` | 12.000 × 1.2 do lỗi gán, ra **14.400 VND** | **12.000 VND** |

- TC2 chỉ bị ảnh hưởng bởi lỗi 2 (gán `=`), vì nhánh ≤ 2 km vẫn đúng.
- TC1 bị ảnh hưởng bởi cả hai lỗi.

## 3. Mã nguồn đã sửa

Xem tệp `grab_fare_debug.c` trong cùng thư mục.

**Kiểm chứng sau khi sửa:**

| Đầu vào | Kết quả |
|---|---|
| `3` / `0` | 16500 VND |
| `1.5` / `0` | 12000 VND |
| `4` / `1` | 25200 VND |

## 4. Biên dịch và chạy

```bash
gcc -Wall -o grab_fare_debug grab_fare_debug.c
./grab_fare_debug
```
