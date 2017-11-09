#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//fonksiyon oluşturma
int menu();
int bagla();
int kopyala();
int grub();
int kes();
int clear();
int format();
int makina();
int dil();
int kullanici();
//çevresel değişken tanımlama
char disk[50];
char hedef[50];
//renk için değişkenler
char* r30 = "\033[30;1m";
char* r31 = "\033[31;1m";
char* r32 = "\033[32;1m";
char* r33 = "\033[33;1m";
char* r34 = "\033[34;1m";
char* r35 = "\033[35;1m";
char* r36 = "\033[36;1m";
char* r37 = "\033[37;1m";
char* son = " \033[0m";
int version = 1;
int main(){
int i = 8; 
clear(); 
while (i != 0){ 
		i = menu();
	if(i == 1){format();}
	if(i == 2){bagla();}
	if(i == 3){kopyala();}
	if(i == 4){grub();}
	if(i == 5){kullanici();}
	if(i == 6){makina();}
	if(i == 7){kes();}
	if(i == 8){dil();}
	if(i == 9){clear();}
} 
}

int clear(){
printf("\x1b[3J\x1b[H\x1b[2J"); 
return 0; 
}

int menu(){
int i = 0; 
printf("%sGNU/Linux kurucu %sv%d%s \n%s%s",r37,r31,version,r37,son,"\n"); 
printf("%s1%s Disk formatlama%s%s",r31,r37,son,"\n"); 
printf("%s2%s Dizin Bağlama%s%s",r31,r37,son,"\n"); 
printf("%s3%s Dosya Koplayala%s%s",r31,r37,son,"\n"); 
printf("%s4%s Grub Kurulumu%s%s",r31,r37,son,"\n"); 
printf("%s5%s Kullanıcı oluşturma%s%s",r31,r37,son,"\n"); 
printf("%s6%s Makina adı ayarlama%s%s",r31,r37,son,"\n"); 
printf("%s7%s Dizin bağı kesme%s%s",r31,r37,son,"\n"); 
printf("%s8%s Dil ayarla(Debian)%s%s",r31,r37,son,"\n"); 
printf("%s9%s Ekranı temizle%s%s",r31,r37,son,"\n"); 
printf("%s0%s Çıkış%s%s",r31,r37,son,"\n"); 
printf("\033[44;1m"); 
scanf("%d",&i); 
printf("\033[0m"); 
if (i > 8 || i < 0){ 
		printf("\033[31;1mUyarı:\033[36;1mGeçersiz seçenek girdiniz\033[0m\n");
}
return i; 
}

int format(){
printf("%sFormatlanacak diski girin%s(ext4)%s\n",r31,son,r37); 
system("ls /dev/sd*"); 
system("ls /dev/mmcblk* 2> /dev/null"); 
printf("%s",son); 
printf("\033[44;1m"); 
scanf("%s",&disk); 
printf("\033[0m"); 
char kod[100] = "[ -b "; 
strcat(kod,disk); 
strcat(kod," ]"); 
if (system(kod) != 0){ 
		printf("\033[31;1mUyarı:\033[36;1mGirmiş olduğunuz disk mevcut değil\033[0m\n");
}else{ 
		strcpy(kod,"umount ");
		strcat(kod,disk);
		system(kod);
		strcpy(kod,"mkfs.ext4 ");
		strcat(kod,disk);
		system(kod);
} 
}

int bagla(){
printf("%s1%s Kaynak bağlama%s%s",r31,r37,son,"\n"); 
printf("%s2%s Hedef bağlama%s%s",r31,r37,son,"\n"); 
printf("%s3%s /dev /sys /proc Bağla%s%s",r31,r37,son,"\n"); 
printf("%s0%s Geri%s%s",r31,r37,son,"\n"); 
printf("\033[44;1m"); 
int i = 0; 
scanf("%d",&i); 
printf("\033[0m"); 
if (i > 3 || i < 0){ 
	printf("\033[31;1mUyarı:\033[36;1mGeçersiz seçenek girdiniz\033[0m\n"); 
	}
if(i == 1){ 
		printf("%sKaynak girin%s(loop veya squashfs)\n",r31,son);
		printf("\033[44;1m");
		scanf("%s",&disk);
		printf("\033[0m");
		char kod[100] = "[ -b ";
		strcat(kod,disk);
		strcat(kod," ]");
		if (system(kod) != 0){
		printf("\033[31;1mUyarı:\033[36;1mGirmiş olduğunuz kaynak mevcut değil\033[0m\n"); 
		}else{
		system("mkdir /source 2> /dev/null"); 
		strcpy(kod,"umount "); 
		strcat(kod,disk); 
		system(kod); 
		strcpy(kod,"mount "); 
		strcat(kod,disk); 
		strcat(kod," /source"); 
		system(kod); 
		}
} 
if(i == 2){ 
		printf("%sHedef girin%s(ext4)%s\n",r31,son,r37);
		system("ls /dev/sd*");
		system("ls /dev/mmcblk* 2> /dev/null");
		printf("%s",son);
		printf("\033[44;1m");
		scanf("%s",&disk);
		printf("\033[0m");
		char kod[100] = "[ -b ";
		strcat(kod,disk);
		strcat(kod," ]");
		if (system(kod) != 0){
		printf("\033[31;1mUyarı:\033[36;1mGirmiş olduğunuz disk mevcut değil\033[0m\n"); 
		}else{
		strcpy(hedef,disk); 
		system("mkdir /target 2> /dev/null"); 
		strcpy(kod,"umount "); 
		strcat(kod,disk); 
		system(kod); 
		strcpy(kod,"mount "); 
		strcat(kod,disk); 
		strcat(kod," /target"); 
		system(kod); 
		}
		
} 
if(i == 3){ 
		system("mount --bind /dev/ /target/dev/");
		system("mount --bind /dev/pts/ /target/dev/pts");
		system("mount --bind /sys/ /target/sys/");
		system("mount --bind /proc/ /target/proc/");
} 
	
}

int kopyala(){
if (system("[ -d /source/bin/ ] ") != 0){ 
		printf("\033[31;1mUyarı:\033[36;1mKaynak henüz bağlanmamış\033[0m\n");
}else{ 
		printf("\033[31;1mDosyalar Kopyalanıyor:\033[36;1mLütfen Bekleyin...\033[0m%s\n",r37);
		system("cp -prf /source/* /target");
		printf("\033[31;1mFstab yazılıyor:\033[36;1mproc\033[0m%s (/proc)\n",r37);
		system("echo \"proc\t/proc\tproc\tdefaults\t0\t0\" > /target/etc/fstab");
		char kod[100] = "echo \"";
		strcat(kod,hedef);
		printf("\033[31;1mFstab yazılıyor:\033[36;1m%s\033[0m%s (/)\n",hedef,r37);
		strcat(kod,"\t/\text4\trw,errors=remount-ro\t0\t1\" >> /target/etc/fstab");
		system(kod);
		printf("%s\n",son);
} 
}

int grub(){
	printf("%sGrub kurulacak diski girin%s%s\n",r31,son,r37);
	system("ls /dev/sd*");
	system("ls /dev/mmcblk* 2> /dev/null");
	printf("%s",son);
	printf("\033[44;1m");
	scanf("%s",&disk);
	printf("\033[0m");
	char kod[100] = "[ -b ";
	strcat(kod,disk);
	strcat(kod," ]");
	if (system(kod) != 0){
	printf("\033[31;1mUyarı:\033[36;1mGirmiş olduğunuz disk mevcut değil\033[0m\n"); 
	}else{
		if (system("[ -d /target/bin/ ] ") != 0){
			printf("\033[31;1mUyarı:\033[36;1mHedef henüz bağlanmamış\033[0m\n");
		}else{
			strcpy(kod,"chroot /target/ grub-install ");
			strcat(kod,disk);
			system(kod);
			strcpy(kod,"chroot /target/ update-grub ");
			strcat(kod,disk);
			system(kod);
		}
	}
}

int kullanici(){
	if (system("[ -d /target/bin/ ] ") != 0){
		printf("\033[31;1mUyarı:\033[36;1mHedef henüz bağlanmamış\033[0m\n");
	}else{
		char user[50];
		char kod[100];
		printf("%sYeni kullanıcı adı girin%s\n",r31,son,r37);
		printf("\033[44;1m");
		scanf("%s",&user);
		printf("\033[0m");
		strcpy(kod,"chroot /target/ adduser ");
		strcat(kod,user);
		system(kod);
	}
}

int makina(){
	if (system("[ -d /target/bin/ ] ") != 0){
		printf("\033[31;1mUyarı:\033[36;1mHedef henüz bağlanmamış\033[0m\n");
	}else{
		char machine[50];
		char kod[100];
		printf("%sMakina adı girin%s\n",r31,son,r37);
		printf("\033[44;1m");
		scanf("%s",&machine);
		printf("\033[0m");
		strcpy(kod,"echo \"");
		strcat(kod,machine);
		strcpy(kod,"\" > /target/etc/hostname");
		system(kod);
	}
}

int kes(){
	char kod[100]="";
	if (system("[ -d /target/bin/ ] ") != 0){
		printf("\033[31;1mUyarı:\033[36;1mHedef henüz bağlanmamış\033[0m\n");
	}else{
		strcpy(kod,"umount -Rf /target/* 2> /dev/null");
		system(kod);
		strcpy(kod,"umount -Rf /target/ 2> /dev/null");
		system(kod);
	}
	if (system("[ -d /source/bin/ ] ") != 0){
		printf("\033[31;1mUyarı:\033[36;1mKaynak henüz bağlanmamış\033[0m\n");
	}else{
		strcpy(kod,"umount -Rf /source/ 2> /dev/null");
		system(kod);
	}
}

int dil(){
	if (system("[ -d /target/bin/ ] ") != 0){
		printf("\033[31;1mUyarı:\033[36;1mHedef henüz bağlanmamış\033[0m\n");
	}else{
		if (system("[ -d /target/var/lib/dpkg ] ") != 0){
			printf("\033[31;1mUyarı:\033[36;1mÜzgünüz:Dağıtımınız debian/ubuntu tabanlı değil\nBu işlem gerçeklendirilemez\033[0m\n");
		}else{
			system("chroot /target dpkg-reconfigure locales");
	}
	}
}
