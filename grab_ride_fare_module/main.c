#include <stdio.h>

/*
 * Chuong trinh: Trip Fare Module - Mo-dun tinh cuoc chuyen xe GrabRide
 * Chuan: C11 / ANSI C
 * Pham vi: chi dung double, int, scanf, printf, if / else
 *
 * Luong du lieu (Data Flow):
 *   [Nhap] -> [Kiem tra hop le] -> [Tinh cuoc co ban] -> [Tinh phu phi] -> [In hoa don]
 */

int main() {
    /* ----- Khai bao hang so nghiep vu ----- */
    const double opening_fare = 12000.0;    /* Gia mo cua cho 2 km dau (VND) */
    const double opening_distance = 2.0;    /* Quang duong gia mo cua (km) */
    const double price_per_km = 4500.0;     /* Don gia moi km tiep theo (VND/km) */
    const double surge_rate = 0.2;          /* Phu phi 20% tren cuoc co ban */

    /* ----- Khai bao bien ----- */
    double distance_km = 0.0;   /* Khoang cach thuc te (km) */
    int is_surge = 0;           /* 1: mua/cao diem, 0: binh thuong */
    double base_fare = 0.0;     /* Cuoc co ban (VND) */
    double surge_fee = 0.0;     /* Tien phu phi phat sinh (VND) */
    double total_fare = 0.0;    /* Tong cuoc thanh toan (VND) */

    /* ================= BUOC 1: NHAP DU LIEU ================= */
    printf("Nhap khoang cach di chuyen (km): ");
    /* scanf tra ve so gia tri doc duoc; khac 1 la nhap sai dinh dang (vd: chu cai) */
    if (scanf("%lf", &distance_km) != 1) {
        printf("LOI: Khoang cach sai dinh dang. Tu choi xu ly.\n");
        return 1;
    }

    printf("Troi mua hoac gio cao diem? (1: Co, 0: Khong): ");
    if (scanf("%d", &is_surge) != 1) {
        printf("LOI: Trang thai phu phi sai dinh dang. Tu choi xu ly.\n");
        return 1;
    }

    /* ================= BUOC 2: KIEM TRA HOP LE ================= */
    /* Phan nay hoan toan tach roi phan tinh tien: sai la thoat, khong tinh gi ca.
     * Viet dang phu dinh de gia tri dac biet nhu nan cung bi chan. */
    if (!(distance_km > 0.0)) {
        printf("LOI: Khoang cach khong hop le (%.2f km). Phai lon hon 0. Tu choi xu ly.\n", distance_km);
        return 1;
    }

    /* Trang thai phu phi chi duoc la 0 hoac 1 (dung && de gop 2 dieu kien vao 1 cau lenh if) */
    if (is_surge != 0 && is_surge != 1) {
        printf("LOI: Trang thai phu phi khong hop le (%d). Chi nhan 0 hoac 1. Tu choi xu ly.\n", is_surge);
        return 1;
    }

    /* ================= BUOC 3: TINH CUOC CO BAN ================= */
    if (distance_km <= opening_distance) {
        /* Dung hoac duoi 2 km: giu nguyen gia mo cua, khong giam theo ti le */
        base_fare = opening_fare;
    } else {
        /* Tren 2 km: gia mo cua + phan vuot qua 2 km */
        base_fare = opening_fare + (distance_km - opening_distance) * price_per_km;
    }

    /* ================= BUOC 4: TINH PHU PHI ================= */
    if (is_surge == 1) {
        surge_fee = base_fare * surge_rate;
    } else {
        surge_fee = 0.0;
    }

    total_fare = base_fare + surge_fee;

    /* ================= BUOC 5: IN HOA DON ================= */
    printf("\n========== HOA DON CHUYEN XE GRABRIDE ==========\n");
    printf("Khoang cach          : %.2f km\n", distance_km);
    if (is_surge == 1) {
        printf("Trang thai           : Mua / Gio cao diem (+20%%)\n");
    } else {
        printf("Trang thai           : Binh thuong\n");
    }
    printf("Cuoc co ban          : %.2f VND\n", base_fare);
    printf("Tien phu phi         : %.2f VND\n", surge_fee);
    printf("------------------------------------------------\n");
    printf("TONG CHI PHI THANH TOAN: %.2f VND\n", total_fare);

    return 0;
}
