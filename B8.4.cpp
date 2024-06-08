#include <iostream>
#include <string>
#include<iomanip>
using namespace std;

struct Date {
  int ngay, thang, nam;
};

class GiaoDich {
protected:
    int maGiaoDich;
    Date ngayGiaoDich;
    double donGia;
    int soLuong;

public:
    GiaoDich() {}
    GiaoDich(int maGiaoDich, Date ngayGiaoDich, double donGia, int soLuong) {
        this->maGiaoDich = maGiaoDich;
        this->ngayGiaoDich = ngayGiaoDich;
        this->donGia = donGia;
        this->soLuong = soLuong;
    }
    virtual void Nhap() {
        cout << "\t[-] Nhap ma giao dich: ";
        cin >> maGiaoDich;
        cout << "\t[-] Nhap ngay/thang/nam: ";
        cin >> ngayGiaoDich.ngay >> ngayGiaoDich.thang >> ngayGiaoDich.nam;
        cout << "\t[-] Nhap don gia: ";
        cin >> donGia;
        cout << "\t[-] Nhap so luong: ";
        cin >> soLuong;
    }
    virtual void In() {
        cout << "\t[-] Ma giao dich: " << maGiaoDich << endl
             << "\t[-] Ngay/thang/nam: " << ngayGiaoDich.ngay << "/" << ngayGiaoDich.thang << "/" << ngayGiaoDich.nam << endl
             << "\t[-] Don gia: " << fixed << setprecision(2)  << donGia << endl
             << "\t[-] So luong: " << soLuong << endl;
    }
    virtual double tinhThanhTien() = 0;
    int getSL() { return soLuong; }
    double getDG() { return donGia; }
    Date getDate() { return ngayGiaoDich; }
};

class GiaoDichVang : public GiaoDich {
    string loaiVang;
public:
    GiaoDichVang() : GiaoDich() {}
    GiaoDichVang(int maGiaoDich, Date ngayGiaoDich, double donGia, int soLuong, string loaiVang): GiaoDich(maGiaoDich, ngayGiaoDich, donGia, soLuong),loaiVang(loaiVang) {}
    void Nhap() {
        GiaoDich::Nhap();
        cout << "\t[-] Nhap loai vang: ";
        cin >> loaiVang;
    }
    void In() {
        GiaoDich::In();
        cout << "\t[-] Loai vang: " << loaiVang << endl
             << "\t[-] Thanh tien: " << fixed << setprecision(2) << tinhThanhTien() << endl;
    }
    double tinhThanhTien() { return soLuong * donGia; }
};

class GiaoDichTienTe : public GiaoDich {
    string loaiTien;
    double tiGia;

public:
    GiaoDichTienTe() : GiaoDich() {}
    GiaoDichTienTe(int maGiaoDich, Date ngayGiaoDich, double donGia, int soLuong, string loaiTien, double tiGia): GiaoDich(maGiaoDich, ngayGiaoDich, donGia, soLuong),loaiTien(loaiTien), tiGia(tiGia) {}
    void Nhap() {
        GiaoDich::Nhap();
        cout << "\t[-] Nhap loai tien (USD/EURO/VND): ";
        cin >> loaiTien;
        cout << "\t[-] Nhap ti gia: ";
        cin >> tiGia;
    }
    void In() {
        GiaoDich::In();
        cout << "\t[-] Loai tien: " << loaiTien << endl
             << "\t[-] Thanh tien: " << fixed << setprecision(2) << tinhThanhTien() << endl;
    }
    double tinhThanhTien() {
        if (loaiTien == "VND") {
            return soLuong * donGia;
        } 
        else {
            return soLuong * donGia * tiGia;
        }
    }
};

int MAX = 100;

void NhapDanhSachGiaoDichVang(GiaoDichVang ds[], int &n) {
    cout << "Nhap so luong giao dich vang: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "Nhap thong tin giao dich vang thu " << i + 1 << ": " << endl;
        ds[i].Nhap();
    }
}

void NhapDanhSachGiaoDichTienTe(GiaoDichTienTe ds[], int &n) {
    cout << "Nhap so luong giao dich tien te: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "Nhap thong tin giao dich tien te thu " << i + 1 << ": " << endl;
        ds[i].Nhap();
    }
}

void XuatDanhSachGiaoDichVang(GiaoDichVang ds[], int n) {
    for (int i = 0; i < n; ++i) {
        ds[i].In();
        cout << endl;
    }
}

void XuatDanhSachGiaoDichTienTe(GiaoDichTienTe ds[], int n) {
    for (int i = 0; i < n; ++i) {
        ds[i].In();
        cout << endl;
    }
}

void TinhTongSoLuong(GiaoDichVang dsVang[], int nVang, GiaoDichTienTe dsTienTe[], int nTienTe) {
    int tongVang = 0, tongTienTe = 0;
    for (int i = 0; i < nVang; ++i) {
        tongVang += dsVang[i].getSL();
    }
    for (int i = 0; i < nTienTe; ++i) {
        tongTienTe += dsTienTe[i].getSL();
    }
    cout << "Tong so luong giao dich vang: " << tongVang << endl;
    cout << "Tong so luong giao dich tien te: " << tongTienTe << endl;
}

void TinhTrungBinhThanhTienTienTe(GiaoDichTienTe ds[], int n) {
    double tongThanhTien = 0;
    for (int i = 0; i < n; ++i) {
        tongThanhTien += ds[i].tinhThanhTien();
    }
    if (n > 0) {
        cout << "Trung binh thanh tien giao dich tien te: " << tongThanhTien / n  << endl;
    }
    else {
        cout << "Khong co giao dich tien te nao." << endl;
    }
}

void XuatGiaoDichDonGiaLonHon1Ty(GiaoDichVang dsVang[], int nVang, GiaoDichTienTe dsTienTe[], int nTienTe) {
    cout << "Giao dich vang co don gia > 1 ty: " << endl;
    for (int i = 0; i < nVang; ++i) {
        if (dsVang[i].getDG() > 1000000000) {
            dsVang[i].In();
            cout << endl;
        }
    }
    cout << "Giao dich tien te co don gia > 1 ty: " << endl;
    for (int i = 0; i < nTienTe; ++i) {
        if (dsTienTe[i].getDG() > 1000000000) {
            dsTienTe[i].In();
            cout << endl;
        }
    }
}

void DemGiaoDichVangNgay2032015(GiaoDichVang ds[], int n) {
    int dem = 0;
    for (int i = 0; i < n; ++i) {
        if (ds[i].getDate().ngay == 20 && ds[i].getDate().thang == 3 && ds[i].getDate().nam == 2015) {
            ++dem;
        }
    }
    cout << "So luong giao dich vang ngay 20/3/2015: " << dem << endl;
}

void sapXepTheoNgay(GiaoDichVang *v, int gdv, GiaoDichTienTe *t, int gdtt) {
    for (int i = 0; i < gdv - 1; ++i) {
        for (int j = 0; j < gdv - i - 1; ++j) {
            if (v[j].getDate().nam < v[j + 1].getDate().ngay || (v[j].getDate().nam == v[j + 1].getDate().nam && v[j].getDate().thang < v[j + 1].getDate().thang) || 
                (v[j].getDate().nam == v[j + 1].getDate().nam && v[j].getDate().thang == v[j + 1].getDate().thang &&v[j].getDG() < v[j + 1].getDate().ngay)) {
                    swap(v[j], v[j + 1]);
            }
        }
    }
    for (int i = 0; i < gdtt - 1; ++i) {
        for (int j = 0; j < gdtt - i - 1; ++j) {
            if (t[j].getDate().nam < t[j + 1].getDate().ngay ||
                (t[j].getDate().nam == t[j + 1].getDate().nam && t[j].getDate().thang < t[j + 1].getDate().thang) ||
                (t[j].getDate().nam == t[j + 1].getDate().nam && t[j].getDate().thang == t[j + 1].getDate().thang &&t[j].getDG() < t[j + 1].getDate().ngay)) {
                    swap(t[j], t[j + 1]);
            }
        }
    }
}

void ThemGiaoDichVaoCuoiDanhSach(GiaoDichVang dsVang[], int &nVang, GiaoDichTienTe dsTienTe[], int &nTienTe) {
    char luaChon;
    cout << "Nhap loai giao dich can them (V: Vang, T: Tien te): ";
    cin >> luaChon;
    if (luaChon == 'V' || luaChon == 'v') {
        if (nVang < MAX) {
            dsVang[nVang].Nhap();
            ++nVang;
        } 
        else {
            cout << "Danh sach giao dich vang da day!" << endl;
        }
    } 
    else if (luaChon == 'T' || luaChon == 't') {
        if (nTienTe < MAX) {
            dsTienTe[nTienTe].Nhap();
            ++nTienTe;
        } 
        else {
            cout << "Danh sach giao dich tien te da day!" << endl;
        }
    }   
    else {
        cout << "Loai giao dich khong hop le!" << endl;
    }
}

void XoaGiaoDichVangNgay2052010(GiaoDichVang ds[], int &n) {
    for (int i = 0; i < n; ++i) {
        if (ds[i].getDate().ngay == 20 && ds[i].getDate().thang == 5 && ds[i].getDate().nam == 2010) {
            for (int j = i; j < n - 1; ++j) {
                ds[j] = ds[j + 1];
            }
        --n;
        cout << "Da xoa cac giao dich vang ngay 20/05/2010." << endl;
        return;
        }
    }
    cout << "Khong tim thay giao dich vang ngay 20/05/2010." << endl;
}

int main() {
    GiaoDichVang dsVang[MAX];
    GiaoDichTienTe dsTienTe[MAX];
    int nVang = 0, nTienTe = 0;
    int luaChon;

    do {
        cout << "===== MENU =====\n";
        cout << "1. Nhap danh sach giao dich vang\n";
        cout << "2. In danh sach giao dich vang\n";
        cout << "3. Nhap danh sach giao dich tien te\n";
        cout << "4. In danh sach giao dich tien te\n";
        cout << "5. Them giao dich\n";
        cout << "6. Xoa giao dich vang ngay 20/5/2010\n";
        cout << "7. Tong so luong giao dich\n";
        cout << "8. Trung binh thanh tien giao dich tien te\n";
        cout << "9. Giao dich co don gia tren 1 ty\n";
        cout << "10. Dem so luong giao dich vang ngay 20/3/2015\n";
        cout << "11. Sap xep danh sach giao dich vang theo ngay\n";
        cout << "12. Sap xep danh sach giao dich tien te theo ngay\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> luaChon;

    switch (luaChon) {
    case 1:
      NhapDanhSachGiaoDichVang(dsVang, nVang);
      break;
    case 2:
      NhapDanhSachGiaoDichTienTe(dsTienTe, nTienTe);
      break;
    case 3:
      XuatDanhSachGiaoDichVang(dsVang, nVang);
      break;
    case 4:
      XuatDanhSachGiaoDichTienTe(dsTienTe, nTienTe);
      break;
    case 5:
      TinhTongSoLuong(dsVang, nVang, dsTienTe, nTienTe);
      break;
    case 6:
      TinhTrungBinhThanhTienTienTe(dsTienTe, nTienTe);
      break;
    case 7:
      XuatGiaoDichDonGiaLonHon1Ty(dsVang, nVang, dsTienTe, nTienTe);
      break;
    case 8:
      DemGiaoDichVangNgay2032015(dsVang, nVang);
      break;
    case 9:
      sapXepTheoNgay(dsVang, nVang, dsTienTe, nTienTe);
      break;
    case 10:
      ThemGiaoDichVaoCuoiDanhSach(dsVang, nVang, dsTienTe, nTienTe);
      break;
    case 11:
      XoaGiaoDichVangNgay2052010(dsVang, nVang);
      break;
    case 0:
      cout << "Thoat chuong trinh." << endl;
      break;
    default:
      cout << "Lua chon khong hop le!" << endl;
    }
  } while (luaChon != 0);

  return 0;
}
