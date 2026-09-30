#include <stdio.h>

/*
 * Chuong trinh: Tinh tong cuoc phi chuyen xe GrabRide (demo tren lop)
 * Chuan: C11 / ANSI C
 *
 * Quy tac nghiep vu:
 *   - Don gia: 20.000 VND/km
 *   - Co ma giam gia (has_promo == 1): giam 20% tren cuoc goc
 *   - Cuoc phi cuoi cung khong duoc thap hon cuoc san 15.000 VND
 */

int main() {
    /* Hang so nghiep vu: doi gia chi can sua tai day */
    const double price_per_km = 20000.0;    /* Don gia moi km (VND) */
    const double promo_rate = 0.8;          /* He so con lai sau khi giam 20% */
    const double minimum_fare = 15000.0;    /* Cuoc san cho tai xe (VND) */

    float distance = 0.0f;      /* Quang duong di chuyen (km) */
    int has_promo = 0;          /* 1: co ma giam gia, 0: khong */
    double total_fare = 0.0;    /* Tong cuoc phi thanh toan (VND) */

    printf("Nhap quang duong di chuyen (km): ");
    /* scanf tra ve so gia tri doc thanh cong; khac 1 la nhap sai dinh dang (vd: chu cai) */
    if (scanf("%f", &distance) != 1) {
        printf("Loi: Du lieu dau vao khong hop le!\n");
        return 1;
    }

    printf("Co ma giam gia khong (1: Co, 0: Khong): ");
    if (scanf("%d", &has_promo) != 1) {
        printf("Loi: Du lieu dau vao khong hop le!\n");
        return 1;
    }

    /* Kiem tra du lieu hop le TRUOC khi tinh toan.
     * distance viet dang phu dinh de gia tri dac biet nhu nan cung bi chan. */
    if (!(distance > 0.0f) || (has_promo != 0 && has_promo != 1)) {
        printf("Loi: Du lieu dau vao khong hop le!\n");
        return 1;
    }

    /* Buoc 1: cuoc goc theo quang duong */
    total_fare = distance * price_per_km;

    /* Buoc 2: ap dung giam gia 20% neu co ma */
    if (has_promo == 1) {
        total_fare = total_fare * promo_rate;
    }

    /* Buoc 3: dam bao cuoc phi khong thap hon cuoc san */
    if (total_fare < minimum_fare) {
        total_fare = minimum_fare;
    }

    printf("Tong cuoc phi: %.2f VNĐ\n", total_fare);

    return 0;
}
