#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<fstream>
using namespace std;
#define numberStudent 100

ifstream docFileDanhSachHocVien;
typedef struct HocVien {
	string MSHV;
	string hoTen;
	string MMH1;
	int DM1;
	string MMH2;
	int DM2;
	string MHP;
	int DMHP;
} hv;
void menu() {
	cout << "______________________________________" << endl;
	cout << "Quan li hoc vien: " << endl;
	cout << "1. Nhap 1 lop" << endl;
	cout << "2. Them 1 hoc vien moi" << endl;
	cout << "3. Xoa 1 hoc vien khi biet MSHV" << endl;
	cout << "4. Xep theo thu tu tang dan cua DM1" << endl;
	cout << "5. Xep theo thu tu tang dan cua DM2" << endl;
	cout << "6. Xep theo thu tu tang dan cua DM1, DM1 bang nhau thi xep tang dan theo DM2" << endl;
	cout << "7. Xuat cac hoc vien khi co MMH" << endl;
	cout << "8. Them mon hoc phu khi co MSHV" << endl;
	cout << "9. Nhap diem mon hoc phu khi co MSHV" << endl;
	cout << "10. Ghi cac thong tin hoc vien da them vao file D:\\DATACLOUD\\hocvien.txt" << endl;
	cout << "11. Mo file D:\\DATACLOUD\\hocvien.txt luu vao bo nho" << endl;
	cout << "12. Xuat danh sach hoc vien ra man hinh" << endl;
	cout << "0. Thoat" << endl;
}
int kiemTraDoDaiChuoi(string str,int stringLimit) {
	/*	Chuc nang: kiem tra do dai chuoi dap ung duoc ki tu yeu cau khong
		Tham so:
		str: chuoi can kiem tra do dai
		stringLimit: do dai chuoi theo quy dinh
		Tra ve:
		ketQua = 0: Do dai chuoi ko hop le
		ketQua = 1: Do dai chuoi hop le
	*/
	int ketQua = 0;
	if(stringLimit >= str.length()) {
		ketQua = 1;
		return ketQua;
	}
	return ketQua;
}
int kiemTraDiemHopLe(int diemCanKiemTra) {
	/*	Chuc nang: Kiem tra so diem nhap thoa 0 den 10 khong
		Tham so:
		diemCanKiemTra: diem khi nhap tu console
	*/
	if(diemCanKiemTra >= 0 && diemCanKiemTra <= 10) {
		return 1;
	} else {
		return 0;
	}
}
void showInputError(string thuocTinh, int soLuongKiTu) {
	/*	Chuc nang: Thong bao chuoi khong hop le khi ki tu vuot qua cho phep
		Tham so:
		thuocTinh: chuoi mon hoc can thong bao ra console
		soLuongKiTu: do dai chuoi theo quy dinh
		soLuongKiTu >= 1, thong bao chuoi k hop le
		soLuongKiTu = 0, thong bao so diem k hop le
	*/
	if(soLuongKiTu == 0) {
		cout << thuocTinh << " nam trong khoang tu 0 den 10!!(la so nguyen)" << endl;
	} else {
		cout << "Luu y: "<< thuocTinh << " toi da "<< soLuongKiTu << " ki tu, vui long nhap lai!!!" << endl;
	}
}
void themHocVien(HocVien sv[],int &studentAdded) {
	/*	Chuc nang: Them hoc vien va cac thuoc tinh hoc vien
		Tham so:
		sv: mang cac hoc vien da nhap
		studentAdded: so luong hoc vien da them vao mang sv[]

		Thuoc tinh mon hoc phu va diem mon hoc phu ban dau ko ton tai
		(chi mot so sv moi co diem mon hoc phu khi su dung chuc nang 8 & 9)
		mac dinh:
		mon hoc phu = NULL
		diem mon hoc phu = -1
	*/
	do {
		cout << "Nhap MSSV: ";
		getline(cin, sv[studentAdded].MSHV);
		if(sv[studentAdded].MSHV.length() > 8) {
			showInputError("MSSV",8);
		}
	} while(kiemTraDoDaiChuoi(sv[studentAdded].MSHV, 8) != 1);
	do {
		cout << "Nhap ho ten: ";
		getline(cin, sv[studentAdded].hoTen);
		if(sv[studentAdded].hoTen.length() > 30) {
			showInputError("ho ten",30);
		}
	} while(kiemTraDoDaiChuoi(sv[studentAdded].hoTen, 30) != 1);
	do {
		cout << "Nhap ma mon hoc 1: ";
		getline(cin, sv[studentAdded].MMH1);
		if(sv[studentAdded].MMH1.length() > 4) {
			showInputError("ma mon hoc 1",4);
		}
	} while(kiemTraDoDaiChuoi(sv[studentAdded].MMH1, 4) != 1);
	do {
		cout << "Nhap diem mon hoc 1: ";
		cin >> sv[studentAdded].DM1;
		if(sv[studentAdded].DM1 < 0 || sv[studentAdded].DM1 > 10) {
			showInputError("diem mon hoc 1",0);
		}
	} while(kiemTraDiemHopLe(sv[studentAdded].DM1) != 1);
	cin.ignore();
	do {
		cout << "Nhap ma mon hoc 2: ";
		getline(cin, sv[studentAdded].MMH2);
		if(sv[studentAdded].MMH2.length() > 4) {
			showInputError("ma mon hoc 2",4);
		}
	} while(kiemTraDoDaiChuoi(sv[studentAdded].MMH2, 4) != 1);
	do {
		cout << "Nhap diem mon hoc 2: ";
		cin >> sv[studentAdded].DM2;
		if(sv[studentAdded].DM2 < 0 || sv[studentAdded].DM2 > 10) {
			showInputError("diem mon hoc 2",0);
		}
	} while(kiemTraDiemHopLe(sv[studentAdded].DM2) != 1);
	cin.ignore();
	sv[studentAdded].MHP = "NULL";
	sv[studentAdded].DMHP = -1;
	studentAdded++;
}
void xuatDanhSach(HocVien sv[],int studentAdded) {
	/*	Chuc nang: Xuat danh sach hoc vien va cac thuoc tinh hoc vien
					Xuat thuoc tinh mon hoc phu neu hoc vien do co mon hoc phu
		Tham so:
		sv: mang cac hoc vien da nhap
		studentAdded: so luong hoc vien da them vao mang sv[]
	*/
	if(studentAdded == 0) {
		cout << "Danh sach sinh vien hien dang trong!" << endl;
	} else {
		for(int i = 0; i < studentAdded; i++) {
			cout << "______________________________________" << endl;
			cout << "STT: " << i + 1 << endl;
			cout << "Ma so hoc vien: " << sv[i].MSHV << endl;
			cout << "Ho & ten hoc vien: " << sv[i].hoTen << endl;
			cout << "Ma mon hoc 1: " << sv[i].MMH1 << endl;
			cout << "Diem mon hoc 1: " << sv[i].DM1 << endl;
			cout << "Ma mon hoc 2: " << sv[i].MMH2 << endl;
			cout << "Diem mon hoc 2: " << sv[i].DM2 << endl;
			if(sv[i].MHP != "NULL"){
				cout << "Mon hoc phu: " << sv[i].MHP << endl;
				cout << "Diem mon hoc phu: " << sv[i].DMHP << endl;
			}
		}
	}
}
void layDuLieuHocVien(HocVien sv[],int &studentAdded) {
	docFileDanhSachHocVien.open("D:\\DATACLOUD\\hocvien.txt");
	/*	chuc nang: doc file hocvien.txt de lay thong tin hoc vien
		Tham so:
			sv: mang cac hoc vien da nhap
			studentAdded: so luong hoc vien da them vao mang sv[]
	*/
	string removeEnterSpace;
//	removeEnterSpace: xoa ki tu \0 sau khi luu xong diem so tranh loi troi lenh
	if(!docFileDanhSachHocVien.is_open()) {
		cout << "Khong tim thay file hocvien.txt, vui long kiem tra lai!!" << endl;
	} else {
		while(!docFileDanhSachHocVien.eof()) {
			getline(docFileDanhSachHocVien, sv[studentAdded].MSHV);
			getline(docFileDanhSachHocVien, sv[studentAdded].hoTen);
			getline(docFileDanhSachHocVien, sv[studentAdded].MMH1);
			docFileDanhSachHocVien >> sv[studentAdded].DM1;
			getline(docFileDanhSachHocVien, removeEnterSpace);
			getline(docFileDanhSachHocVien, sv[studentAdded].MMH2);
			docFileDanhSachHocVien >> sv[studentAdded].DM2;
			getline(docFileDanhSachHocVien, removeEnterSpace);
			getline(docFileDanhSachHocVien, sv[studentAdded].MHP);
			docFileDanhSachHocVien >> sv[studentAdded].DMHP;
			getline(docFileDanhSachHocVien, removeEnterSpace);
			if(!docFileDanhSachHocVien.eof()) {
				studentAdded++;
			}
		}
		cout << "Da luu vao hocvien.txt nhan chuc nang 12 de kiem tra lai!!" << endl;
	}
	docFileDanhSachHocVien.close();
}
void ghiDuLieuHocVien(HocVien sv[],int &studentAdded) {
	ofstream ghiFileDanhSachHocVien("D:\\DATACLOUD\\hocvien.txt",ios::out);
	for(int i = 0; i < studentAdded; i++) {
		ghiFileDanhSachHocVien <<  sv[i].MSHV << endl;
		ghiFileDanhSachHocVien <<  sv[i].hoTen << endl;
		ghiFileDanhSachHocVien <<  sv[i].MMH1 << endl;
		ghiFileDanhSachHocVien <<  sv[i].DM1 << endl;
		ghiFileDanhSachHocVien <<  sv[i].MMH2 << endl;
		ghiFileDanhSachHocVien <<  sv[i].DM2 << endl;
		ghiFileDanhSachHocVien <<  sv[i].MHP << endl;
		ghiFileDanhSachHocVien <<  sv[i].DMHP << endl;
	}
	ghiFileDanhSachHocVien.close();
	cout << "Da ghi du lieu thanh cong!! vao D:\\DATACLOUD\\hocvien.txt de kiem tra" << endl;
}
void xoaHocVien(HocVien sv[],int &studentAdded) {
	/*	Chuc nang: Xoa 1 hoc vien khi thoa MSSV nhap
		Tham so:
		sv: mang cac hoc vien da nhap
		studentAdded: so luong hoc vien da them vao mang sv[]
	*/
	string maSoHocVienCanXoa;
	int viTriCanXoa = -1;
	cout << "Nhap MSHV cua hoc vien can xoa: ";
	getline(cin, maSoHocVienCanXoa);
	//Tim vi tri can xoa
	for(int i = 0; i < studentAdded; i++) {
		if(sv[i].MSHV == maSoHocVienCanXoa) {
			viTriCanXoa = i;
		}
	}
	//Neu vi tri can xoa ton tai
	//tien hanh dich chuyen vi tri cac phan tu viTriCanXoa+1 -> phan tu gan ke cuoi len 1 phan tu
	if(viTriCanXoa != -1) {
		for(int i = viTriCanXoa; i < studentAdded - 1; i++) {
			sv[i] = sv[i + 1];
		}
		studentAdded--;
		cout << "Da xoa hoc vien co MSHV: " << maSoHocVienCanXoa << " !!"<< endl;
		ghiDuLieuHocVien(sv,studentAdded);
	} else {
		//Neu vi tri can xoa khong ton tai (viTriCanXoa = -1)
		//Xuat thong bao, thoat ham
		cout << "Khong co hoc vien co MSHV " << maSoHocVienCanXoa
		     << " vui long kiem tra lai!!" << endl;
	}
}
//=======cau 4=======//
void sortDM1(HocVien sv[],int studentAdded) {
	HocVien cur;
	for(int i=0; i<studentAdded; i++) {
		for(int j=i+1; j<studentAdded; j++) {
			if(sv[i].DM1 > sv[j].DM1) {
				cur = sv[i];
				sv[i] = sv[j];
				sv[j] = cur;
			}
		}
	}
}
//=======cau 5=======//
void sortDM2(HocVien sv[],int studentAdded) {
	HocVien cur;
	for(int i=0; i<studentAdded; i++) {
		for(int j=i+1; j<studentAdded; j++) {
			if(sv[i].DM2 > sv[j].DM2) {
				cur = sv[i];
				sv[i] = sv[j];
				sv[j] = cur;
			}
		}
	}
}
//=======cau 6=======//
void sortDM1_DM2(HocVien sv[],int studentAdded) {
	sortDM1(sv,studentAdded);
	HocVien cur;
	for(int i=0; i<studentAdded; i++) {
		for(int j=i+1; j<studentAdded; j++) {
			if(sv[i].DM2 > sv[j].DM2 && sv[i].DM1 == sv[j].DM1) {
				cur = sv[i];
				sv[i] = sv[j];
				sv[j] = cur;
			}
		}
	}
}
//=======cau 7=======//
void XuatKhiCo_MMH(HocVien sv[],int studentAdded) {
	/*
	check: kiem tra
	check > 0: tim duoc hoc vien voi MMH da nhap
	check = 0: khong tim duoc hoc vien voi MMH da nhap
	*/
	int check=0;
	HocVien cur;
	string mamon_xuat;
	cout << "Nhap MMH cua hoc vien can xuat: ";
	getline(cin, mamon_xuat);
	for(int i=0; i<studentAdded; i++) {
		cur = sv[i];
		if(cur.MMH1 == mamon_xuat || cur.MMH2 == mamon_xuat) {
			cout << "______________________________________" << endl;
			cout << "STT: " << i + 1 << endl;
			cout << "Ma so hoc vien: " << sv[i].MSHV << endl;
			cout << "Ho & ten hoc vien: " << sv[i].hoTen << endl;
			cout << "Ma mon hoc 1: " << sv[i].MMH1 << endl;
			cout << "Diem mon hoc 1: " << sv[i].DM1 << endl;
			cout << "Ma mon hoc 2: " << sv[i].MMH2 << endl;
			cout << "Diem mon hoc 2: " << sv[i].DM2 << endl;
			cout << "Mon hoc phu: " << sv[i].MHP << endl;
			cout << "Diem mon hoc phu: " << sv[i].DMHP << endl;
			check++;
		}
	}
	if(check == 0)
		cout << "Khong co ma mon hoc nay"<<endl;
}
//=======cau 8=======//
int ThemMonHocPhu(HocVien sv[],int studentAdded) {
	/*
	check_MSHV: kiem tra ma so hoc vien co ton tai khong
	return 1: tim duoc hoc vien va them duoc mon phu
	return 0: khong tim duoc hoc vien
	*/
	HocVien cur;
	string check_MSHV;
	cout << "Nhap MSHV cua hoc vien can them mon phu: ";
	getline(cin, check_MSHV);
	for(int i = 0; i<studentAdded; i++) {
		cur = sv[i];
		if(cur.MSHV == check_MSHV) {
			do {
				cout << "Nhap ma mon hoc phu: ";
				getline(cin, sv[i].MHP);
				if(sv[i].MHP.length() > 4) {
					showInputError("ma mon hoc phu",4);
				}
			} while(kiemTraDoDaiChuoi(sv[i].MHP, 4) != 1);
			return 1;
		}
	}
	return 0;
}
//=======cau 9=======//
int NhapDiemMonHocPhu(HocVien sv[],int studentAdded) {
	/*
	check: ham kiem tra 2 truong hop
	check = studentAdded khong tim thay hoc sinh
	studentAdded > check > 0 hoc vien da tim duoc nhung khong co mon hoc phu
	*/
	int check = 0;
	HocVien cur;
	string check_MSHV;
	cout << "Nhap MSHV cua hoc vien can them mon phu: ";
	getline(cin, check_MSHV);
	for(int i = 0; i<studentAdded; i++) {
		cur = sv[i];
		if(cur.MSHV == check_MSHV && cur.MHP != "NULL") {
			cout << "Nhap diem mon hoc phu: ";
			cin >> sv[i].DMHP;
			cin.ignore();
			return 1;
		}
		if(cur.MSHV != check_MSHV) check++;
	}
	if(check == studentAdded)
		return -1;
	else
		return 0;
}

int main() {
	HocVien hv[numberStudent];
	int studentAdded = 0;
	while(true) {
		int choose;
		menu();
		cout << "Nhap lua chon: ";
		cin >> choose;
		cin.ignore();
		switch(choose) {
			case 1: { //Nhap so luong hoc vien lop
				int siSo;
				cout << "Nhap so luong hoc vien cua lop: ";
				cin >> siSo;
				cin.ignore();
				for(int i=0; i<siSo; i++) {
					themHocVien(hv,studentAdded);
				}
				break;
			}
			case 2: { //Them 1 hoc vien
				themHocVien(hv,studentAdded);
				break;
			}
			case 3: { //Xoa 1 hoc vien khi biet MSHV
				xoaHocVien(hv,studentAdded);
				break;
			}
			case 4: { //Sort diem 1
				sortDM1(hv,studentAdded);
				xuatDanhSach(hv,studentAdded);
				break;
			}
			case 5: { //Sort diem 2
				sortDM2(hv,studentAdded);
				xuatDanhSach(hv,studentAdded);
				break;
			}
			case 6: { //Sort diem 1 va 2
				sortDM1_DM2(hv,studentAdded);
				xuatDanhSach(hv,studentAdded);
				break;
			}
			case 7: { //Tim thong tin sinh vien dua theo ma mon hoc
				XuatKhiCo_MMH(hv,studentAdded);
				break;
			}
			case 8: { //Them mon hoc phu cho sv dc nhap mshv
				int check8 = ThemMonHocPhu(hv,studentAdded);
				if(check8 == 0)
					cout << "Khong tim thay hoc vien" << endl;
				else
					cout << "Them mon hoc phu thanh cong" << endl;
				break;
			}
			case 9: { //nhap diem mon hoc phu cho sv co mshv dc nhap
				int check9 = NhapDiemMonHocPhu(hv,studentAdded);
				if(check9 == -1)
					cout << "Khong tim thay hoc vien" << endl;
				if(check9 == 0)
					cout << "Hoc vien khong co mon hoc phu" << endl;
				if(check9 == 1)
					cout << "Nhap diem mon hoc phu thanh cong" << endl;
				break;
			}
			case 10: { //Luu cac thong tin hoc vien vao hocvien.txt
				ghiDuLieuHocVien(hv,studentAdded);
				break;
			}
			case 11: { //Doc du lieu hocvien.txt vao mang sv[]
				layDuLieuHocVien(hv,studentAdded);
				break;
			}
			case 12: { //Xuat danh sach hoc vien
				xuatDanhSach(hv,studentAdded);
				break;
			}
			case 0: { //Thoat chuong trinh
				exit(0);
				break;
			}
			default: { //Thong bao khi case nhap vao k hop le
				cout << "Khong dung cu phap, moi nhap lai!" << endl;
				break;
			}
		}
	}
	return 0;
}
