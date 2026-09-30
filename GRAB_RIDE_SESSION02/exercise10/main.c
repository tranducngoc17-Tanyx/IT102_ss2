#include <stdio.h>

/*
 * Chuong trinh: TripFareEngine - Tinh cuoc chuyen xe GrabRide (phien ban Refactored)
 * Ky thuat: Guard Clauses + Step-by-Step Calculation
 *
 * Luong xu ly gom 3 buoc doc lap:
 *   Buoc 1: Kiem tra du lieu hop le (guard clauses, thoat som neu sai)
 *   Buoc 2: Tinh cuoc co ban theo quang duong
 *   Buoc 3: Nhan he so phu phi neu is_surge == 1  (chi viet MOT lan)
 */

int main() {
    /* Cac hang so nghiep vu: khi doi gia cuoc chi can sua tai day */
    const double base_fare = 12000.0;      /* Cuoc tron goi cho 2 km dau (VND) */
    const double base_distance = 2.0;      /* Quang duong tron goi (km) */
    const double price_per_km = 4500.0;    /* Don gia moi km vuot qua (VND/km) */
    const double surge_multiplier = 1.2;   /* He so phu phi (tang 20%) */

    double distance_km = 0.0;
    int is_surge = 0;
    double total_fare = 0.0;

    /* ---------- NHAP DU LIEU ---------- */
    printf("Nhap quang duong di chuyen (km): ");
    if (scanf("%lf", &distance_km) != 1) {
        printf("LOI: Quang duong sai dinh dang.\n");
        return 1;
    }

    printf("Nhap trang thai phu phi (0: Binh thuong, 1: Xau/Cao diem): ");
    if (scanf("%d", &is_surge) != 1) {
        printf("LOI: Trang thai phu phi sai dinh dang.\n");
        return 1;
    }

    /* ---------- BUOC 1: GUARD CLAUSES ---------- */

    /* Viet dang phu dinh de gia tri dac biet nhu nan cung bi chan */
    if (!(distance_km > 0.0)) {
        printf("LOI: Quang duong khong hop le (%.2f km). Phai lon hon 0.\n", distance_km);
        return 1;
    }

    if (is_surge != 0 && is_surge != 1) {
        printf("LOI: Trang thai phu phi khong hop le (%d). Chi nhan 0 hoac 1.\n", is_surge);
        return 1;
    }

    /* ---------- BUOC 2: CUOC CO BAN THEO QUANG DUONG ---------- */
    if (distance_km <= base_distance) {
        /* Dung 2.0 km van chi tinh 12.000, khong cong phu troi */
        total_fare = base_fare;
    } else {
        total_fare = base_fare + (distance_km - base_distance) * price_per_km;
    }

    /* ---------- BUOC 3: PHU PHI (chi mot cho duy nhat) ---------- */
    if (is_surge == 1) {
        total_fare = total_fare * surge_multiplier;
    }

    printf("Tong cuoc phi chuyen xe: %.2f VND\n", total_fare);

    return 0;
}
