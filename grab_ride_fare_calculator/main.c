#include <stdio.h>

/*
 * Chuong trinh: Tinh cuoc chuyen xe GrabRide (GrabBike / GrabCar)
 * Chuan: C11 / ANSI C
 * Luong xu ly: Nhap -> Kiem tra du lieu -> Tinh cuoc co so -> Tinh phu phi -> In hoa don
 */

int main() {
    int vehicle_type = 0;      /* 1: GrabBike, 2: GrabCar */
    double distance = 0.0;     /* Khoang cach (km) */
    int is_peak_or_rain = 0;   /* 1: co phu phi, 0: binh thuong */

    double base_fare = 0.0;    /* Cuoc co so (VND) */
    double surcharge = 0.0;    /* Phu phi bien doi (VND) */
    double total_fare = 0.0;   /* Tong cuoc thanh toan (VND) */

    /* ---------- BUOC 1: NHAP DU LIEU ---------- */
    printf("Nhap ma loai xe (1: GrabBike, 2: GrabCar): ");
    /* scanf tra ve so gia tri doc thanh cong; khac 1 nghia la nhap sai dinh dang (vd: chu cai) */
    if (scanf("%d", &vehicle_type) != 1) {
        printf("LOI: Ma loai xe sai dinh dang. Huy hoa don.\n");
        return 1;
    }

    printf("Nhap khoang cach di chuyen (km): ");
    if (scanf("%lf", &distance) != 1) {
        printf("LOI: Khoang cach sai dinh dang. Huy hoa don.\n");
        return 1;
    }

    printf("Co phu phi gio cao diem/mua khong (1: Co, 0: Khong): ");
    if (scanf("%d", &is_peak_or_rain) != 1) {
        printf("LOI: Trang thai phu phi sai dinh dang. Huy hoa don.\n");
        return 1;
    }

    /* ---------- BUOC 2: KIEM TRA DU LIEU (truoc moi phep tinh tai chinh) ---------- */

    /* Ma loai xe chi duoc la 1 hoac 2 */
    if (vehicle_type != 1 && vehicle_type != 2) {
        printf("LOI: Ma loai xe khong hop le (%d). Huy hoa don.\n", vehicle_type);
        return 1;
    }

    /* Trang thai phu phi chi duoc la 0 hoac 1 */
    if (is_peak_or_rain != 0 && is_peak_or_rain != 1) {
        printf("LOI: Trang thai phu phi khong hop le (%d). Huy hoa don.\n", is_peak_or_rain);
        return 1;
    }

    /* Cu ly hop le: 0 < distance <= 300.
     * Viet dang phu dinh de cac gia tri dac biet nhu nan cung bi chan
     * (moi phep so sanh voi nan deu sai nen dieu kien "hop le" cung sai). */
    if (!(distance > 0.0 && distance <= 300.0)) {
        printf("LOI: Cu ly bat thuong (%.2f km). Chi chap nhan 0 < km <= 300. Huy hoa don.\n", distance);
        return 1;
    }

    /* ---------- BUOC 3: TINH CUOC CO SO ---------- */
    if (vehicle_type == 1) {
        if (distance <= 2.0) {
            /* Gia san 2 km dau: giu nguyen, khong giam theo ti le */
            base_fare = 12000.0;
        } else {
            base_fare = 12000.0 + (distance - 2.0) * 4500.0;
        }
    } else {
        if (distance <= 2.0) {
            base_fare = 25000.0;
        } else {
            base_fare = 25000.0 + (distance - 2.0) * 10000.0;
        }
    }

    /* ---------- BUOC 4: TINH PHU PHI (20% tren cuoc co so) ---------- */
    if (is_peak_or_rain == 1) {
        surcharge = base_fare * 0.2;
    } else {
        surcharge = 0.0;
    }

    total_fare = base_fare + surcharge;

    /* ---------- BUOC 5: IN HOA DON ---------- */
    printf("\n===== HOA DON CHUYEN XE GRABRIDE =====\n");
    if (vehicle_type == 1) {
        printf("Dich vu        : GrabBike\n");
    } else {
        printf("Dich vu        : GrabCar\n");
    }
    printf("Khoang cach    : %.2f km\n", distance);
    printf("Cuoc co so     : %.0f VND\n", base_fare);
    printf("Phu phi        : %.0f VND\n", surcharge);
    printf("Tong thanh toan: %.0f VND\n", total_fare);

    return 0;
}
