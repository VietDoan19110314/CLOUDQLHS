#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
using namespace std;
#define numberStudent 100

ifstream docFileDanhSachHocVien("/home/ubuntu/environment/Pro1_QLDiemHS/hocvien.txt");
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
	cout << "Student Management: " << endl;
	cout << "1. Enter 1 class" << endl;
	cout << "2. Add 1 new student" << endl;
	cout << "3. Delete 1 student when knowing the student ID" << endl;
	cout << "4. Sort by ascending order of First Score" << endl;
	cout << "5. Sort in ascending order of Second Score" << endl;
	cout << "6. Ranked in ascending order of the 1st Score, if the 1st Score is equal, then the ascending order of the 2nd Score" << endl;
	cout << "7. Export students when subject ID is available" << endl;
	cout << "8. Add an extra subject when there is a student ID" << endl;
	cout << "9. Enter the extra subject score when the student ID is available" << endl;
	cout << "10. Record the information students have added to the file /home/ubuntu/environment/Pro1_QLDiemHS/hocvien.txt" << endl;
	cout << "11. Open file /home/ubuntu/environment/Pro1_QLDiemHS/hocvien.txt and save to memory" << endl;
	cout << "12. Export the list of students to the screen" << endl;
	cout << "0. Exit" << endl;
}
int kiemTraDoDaiChuoi(string str,int stringLimit) {
	int ketQua = 0;
	if(stringLimit >= str.length()) {
		ketQua = 1;
		return ketQua;
	}
	return ketQua;
}
int kiemTraDiemHopLe(int diemCanKiemTra) {
	if(diemCanKiemTra >= 0 && diemCanKiemTra <= 10) {
		return 1;
	} else {
		return 0;
	}
}
void showInputError(string thuocTinh, int soLuongKiTu) {
	if(soLuongKiTu == 0) {
		cout << thuocTinh << " Must be an integer between 0 and 10" << endl;
	} else {
		cout << "Note: "<< thuocTinh << " Up to "<< soLuongKiTu << " characters, please re-enter!!!" << endl;
	}
}
void themHocVien(HocVien sv[],int &studentAdded) {
	do {
		cout << "Enter student ID: ";
		getline(cin, sv[studentAdded].MSHV);
		if(sv[studentAdded].MSHV.length() > 8) {
			showInputError("Student ID",8);
		}
	} while(kiemTraDoDaiChuoi(sv[studentAdded].MSHV, 8) != 1);
	do {
		cout << "Enter name: ";
		getline(cin, sv[studentAdded].hoTen);
		if(sv[studentAdded].hoTen.length() > 30) {
			showInputError("Name",30);
		}
	} while(kiemTraDoDaiChuoi(sv[studentAdded].hoTen, 30) != 1);
	do {
		cout << "Enter the first course ID: ";
		getline(cin, sv[studentAdded].MMH1);
		if(sv[studentAdded].MMH1.length() > 4) {
			showInputError("First course ID",4);
		}
	} while(kiemTraDoDaiChuoi(sv[studentAdded].MMH1, 4) != 1);
	do {
		cout << "Enter the score of the first subject: ";
		cin >> sv[studentAdded].DM1;
		if(sv[studentAdded].DM1 < 0 || sv[studentAdded].DM1 > 10) {
			showInputError("The score of the first subject",0);
		}
	} while(kiemTraDiemHopLe(sv[studentAdded].DM1) != 1);
	cin.ignore();
	do {
		cout << "Enter the second course code: ";
		getline(cin, sv[studentAdded].MMH2);
		if(sv[studentAdded].MMH2.length() > 4) {
			showInputError("The score of the second subject",4);
		}
	} while(kiemTraDoDaiChuoi(sv[studentAdded].MMH2, 4) != 1);
	do {
		cout << "Enter the score of the second subject: ";
		cin >> sv[studentAdded].DM2;
		if(sv[studentAdded].DM2 < 0 || sv[studentAdded].DM2 > 10) {
			showInputError("The score of the second subject",0);
		}
	} while(kiemTraDiemHopLe(sv[studentAdded].DM2) != 1);
	cin.ignore();
	sv[studentAdded].MHP = "NULL";
	sv[studentAdded].DMHP = -1;
	studentAdded++;
}
void xuatDanhSach(HocVien sv[],int studentAdded) {
	if(studentAdded == 0) {
		cout << "Student list is currently empty!" << endl;
	} else {
		for(int i = 0; i < studentAdded; i++) {
			cout << "______________________________________" << endl;
			cout << "Number: " << i + 1 << endl;
			cout << "Student ID: " << sv[i].MSHV << endl;
			cout << "Student name: " << sv[i].hoTen << endl;
			cout << "First course ID: " << sv[i].MMH1 << endl;
			cout << "First subject score: " << sv[i].DM1 << endl;
			cout << "Second course ID: " << sv[i].MMH2 << endl;
			cout << "Second subject score: " << sv[i].DM2 << endl;
			if(sv[i].MHP != "NULL"){
				cout << "Extra subject: " << sv[i].MHP << endl;
				cout << "Extra subject score: " << sv[i].DMHP << endl;
			}
		}
	}
}
void layDuLieuHocVien(HocVien sv[],int &studentAdded) {
	string removeEnterSpace;
	if(!docFileDanhSachHocVien.is_open()) {
		cout << "Hocvien.txt file not found, please check again!!!!" << endl;
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
		cout << "Saved to file hocvien.txt, press function 12 to check again !!" << endl;
	}
	docFileDanhSachHocVien.close();
}
void ghiDuLieuHocVien(HocVien sv[],int &studentAdded) {
	ofstream ghiFileDanhSachHocVien("/home/ubuntu/environment/Pro1_QLDiemHS/hocvien.txt",ios::out);
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
	cout << "Recorded data successfully!! Go to /home/ubuntu/environment/Pro1_QLDiemHS/hocvien.txt to check." << endl;
}
void xoaHocVien(HocVien sv[],int &studentAdded) {
	string maSoHocVienCanXoa;
	int viTriCanXoa = -1;
	cout << "Enter the student ID of the student to be deleted: ";
	getline(cin, maSoHocVienCanXoa);
	for(int i = 0; i < studentAdded; i++) {
		if(sv[i].MSHV == maSoHocVienCanXoa) {
			viTriCanXoa = i;
		}
	}
	if(viTriCanXoa != -1) {
		for(int i = viTriCanXoa; i < studentAdded - 1; i++) {
			sv[i] = sv[i + 1];
		}
		studentAdded--;
		cout << "Deleted student whose student ID is: " << maSoHocVienCanXoa << " !!"<< endl;
		ghiDuLieuHocVien(sv,studentAdded);
	} else {
		cout << "There is no student whose student ID is: " << maSoHocVienCanXoa
		     << " Please check again!!" << endl;
	}
}

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

void XuatKhiCo_MMH(HocVien sv[],int studentAdded) {
	int check=0;
	HocVien cur;
	string mamon_xuat;
	cout << "Enter the student's subject ID to export: ";
	getline(cin, mamon_xuat);
	for(int i=0; i<studentAdded; i++) {
		cur = sv[i];
		if(cur.MMH1 == mamon_xuat || cur.MMH2 == mamon_xuat) {
			cout << "______________________________________" << endl;
			cout << "Number: " << i + 1 << endl;
			cout << "Student ID: " << sv[i].MSHV << endl;
			cout << "Student name: " << sv[i].hoTen << endl;
			cout << "First course ID: " << sv[i].MMH1 << endl;
			cout << "First subject score: " << sv[i].DM1 << endl;
			cout << "Second course ID: " << sv[i].MMH2 << endl;
			cout << "Second subject score: " << sv[i].DM2 << endl;
			cout << "Extra subject: " << sv[i].MHP << endl;
			cout << "Extra subject score: " << sv[i].DMHP << endl;
			check++;
		}
	}
	if(check == 0)
		cout << "This course code is not available"<<endl;
}

int ThemMonHocPhu(HocVien sv[],int studentAdded) {
	HocVien cur;
	string check_MSHV;
	cout << "Enter the student number of the student who needs to add extra subjects";
	getline(cin, check_MSHV);
	for(int i = 0; i<studentAdded; i++) {
		cur = sv[i];
		if(cur.MSHV == check_MSHV) {
			do {
				cout << "Enter the extra subject ID: ";
				getline(cin, sv[i].MHP);
				if(sv[i].MHP.length() > 4) {
					showInputError("Extra subject ID",4);
				}
			} while(kiemTraDoDaiChuoi(sv[i].MHP, 4) != 1);
			return 1;
		}
	}
	return 0;
}

int NhapDiemMonHocPhu(HocVien sv[],int studentAdded) {
	int check = 0;
	HocVien cur;
	string check_MSHV;
	cout << "Enter the student number of the student who needs to add an extra subject: ";
	getline(cin, check_MSHV);
	for(int i = 0; i<studentAdded; i++) {
		cur = sv[i];
		if(cur.MSHV == check_MSHV && cur.MHP != "NULL") {
			cout << "Enter extra subject score: ";
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
		cout << "Enter selection: ";
		cin >> choose;
		cin.ignore();
		switch(choose) {
			case 1: { 
				int siSo;
				cout << "Enter the number of students in the class: ";
				cin >> siSo;
				cin.ignore();
				for(int i=0; i<siSo; i++) {
					themHocVien(hv,studentAdded);
				}
				break;
			}
			case 2: {
				themHocVien(hv,studentAdded);
				break;
			}
			case 3: {
				xoaHocVien(hv,studentAdded);
				break;
			}
			case 4: { 
				sortDM1(hv,studentAdded);
				xuatDanhSach(hv,studentAdded);
				break;
			}
			case 5: {
				sortDM2(hv,studentAdded);
				xuatDanhSach(hv,studentAdded);
				break;
			}
			case 6: {
				sortDM1_DM2(hv,studentAdded);
				xuatDanhSach(hv,studentAdded);
				break;
			}
			case 7: { 
				XuatKhiCo_MMH(hv,studentAdded);
				break;
			}
			case 8: { 
				int check8 = ThemMonHocPhu(hv,studentAdded);
				if(check8 == 0)
					cout << "Student not found" << endl;
				else
					cout << "Successfully added extra subject" << endl;
				break;
			}
			case 9: { 
				int check9 = NhapDiemMonHocPhu(hv,studentAdded);
				if(check9 == -1)
					cout << "Student not found" << endl;
				if(check9 == 0)
					cout << "Students with no extra subject" << endl;
				if(check9 == 1)
					cout << "Successfully entered extra subject score" << endl;
				break;
			}
			case 10: { 
				ghiDuLieuHocVien(hv,studentAdded);
				break;
			}
			case 11: { 
				layDuLieuHocVien(hv,studentAdded);
				break;
			}
			case 12: { 
				xuatDanhSach(hv,studentAdded);
				break;
			}
			case 0: { 
				exit(0);
				break;
			}
			default: { 
				cout << "Incorrect syntax, please re-enter !!!" << endl;
				break;
			}
		}
	}
	return 0;
}
