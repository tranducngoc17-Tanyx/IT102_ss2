#include <stdio.h>

int main() {
    float distance;
    int is_raining;
    double total_fare = 0.0;

    printf("Nhap quang duong di chuyen (km): ");
    scanf("%f", &distance);

    printf("Thoi tiet co mua khong (1: Co, 0: Khong): ");
    scanf("%d", &is_raining);

    // Tinh cuoc phi co ban theo quang duong
    if (distance <= 2.0) {
        total_fare = 12000.0;
    } else {
        // 2 km dau: 12000, phan vuot qua 2 km: 4500/km
        total_fare = 12000.0 + (distance - 2.0) * 4500.0;
    }

    // Kiem tra phu phi thoi tiet (dung == de so sanh)
    if (is_raining == 1) {
        total_fare = total_fare * 1.2;
    }

    printf("Tong cuoc phi chuyen xe: %.0f VND\n", total_fare);

    return 0;
}
