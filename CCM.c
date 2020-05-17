#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{     //구조체 선언
    char name[60];
} CCM;
 
int addCCM(CCM *s); //데이터 추가 함수
void readCCM(CCM s); // 데이터 출력 함수
void loopRead(CCM *s[], int count); //readCCM함수 반복
int selectDataNo(CCM *s[], int count); //데이터 수정, 삭제 시 번호 선택 함수
int updateCCM(CCM *s); // 데이터 수정 함수
void saveData(CCM *s[], int count); //파일입력 함수
int loadData(CCM *s[]); //파일출력 함수
int searchName(CCM *s[], int curi); //검색 함수
int selectMenu();      //메인메뉴 출력 함수
  

int main(void){
    CCM *sp[1000];    //구조체 포인터 배열 사용
    int count = 0, menu; 
    int curi =0;    //배열의 위치를 표시하기 위한 변수
    int no=0;   // 취소, 수정시 선택한 번호를 저장하는 변수
    int deleteok=0; //취소확인을 위한 변수


    count = loadData(sp);
    curi = count;

    printf("***저장파일의 이름은 반드시 'CCM악보 모음집'으로 저장해주세요!***\n\n");

    while (1){
        menu = selectMenu();    // 메뉴호출
        if (menu == 0) break;   //메뉴종료값이 입력되면 종료
        if (menu == 1){ //조회
            if(count<=0)    //데이터 유무 확인
            { 
                printf("데이터가 없습니다!\n");
                continue;
            }
            else loopRead(sp, curi);     //
        }
        else if (menu == 2){ //추가
            sp[curi] = (CCM*)malloc(sizeof(CCM));
            count+=addCCM(sp[curi++]);
            printf("=>추가됨!\n");
        }
        else if (menu == 3){ //수정
            if(count<=0)    //데이터 유무 확인
            { 
                printf("데이터가 없습니다!\n");
                continue;
            }

            int no = selectDataNo(sp, curi); //번호 선택
            
            if(no==0){ //취소
                printf("=> 취소됨!\n");
                continue;
            }
            
            updateCCM(sp[no-1]); //수정
        }
        else if (menu == 4){ //삭제
            if(count<=0)    //데이터 유무 확인
            { 
                printf("데이터가 없습니다!\n");
                continue;
            }
            
            int no = selectDataNo(sp, curi); //번호 선택
            if(no==0){ //취소
                printf("=>취소됨!\n");
                continue;
            }
            printf("\n정말로 삭제하시겠습니까?(삭제 :1)"); //취소 확인
            scanf("%d", &deleteok);
            
            if(deleteok == 1){
                if(sp[no-1]) //삭제
                {free(sp[no-1]);
                 printf("=> 삭제됨!\n");
                }
                sp[no-1]=NULL;
                count --; 
            }
        }
        else if(menu==5){
            if(count==0)
            printf("데이터가 없습니다!\n");
            else saveData(sp, curi);
        }
        else if(menu==6){
            if(count==0)
            printf("데이터가 없습니다!\n");
	    else{
		int n=1;
		while(n==1){
            	 n = searchName(sp, curi);
	   	}
	    }
        }
    }
    printf("종료됨!\n");
    return 0;
}
int addCCM(CCM *s)
{   
    getchar();
    printf("\n악보 이름을 입력하세요 : ");
    fgets(s->name,60,stdin);
    return 1;
}

void readCCM(CCM s)
{
  printf("%s", s.name);
}

void loopRead(CCM *s[], int count)
{
    printf("\n No name\n");
    printf("===================================================\n");
    for(int i=0; i <count ; i++){
        if(s[i]==NULL) continue;
        printf("%3d ", i+1);
        readCCM(*s[i]);
    }
    printf("\n");
}

int selectDataNo(CCM *s[], int count)
{
    int no;
    loopRead(s, count);
    printf("\n번호는 (취소 :0)? ");
   
    while(1){
        if(scanf("%d", &no)==0){
            printf("숫자를 입력하세요 : ");
            rewind(stdin);
            continue;
        }
        else{
            if(no<0||no>count){
                printf("올바른 번호를 입력하세요 : ");
            }
            else break;
        }
        
    }

    return no;

}

int updateCCM(CCM *s)
{
    getchar();
    printf("\n새로운 악보 이름을 입력하세요 : ");
    fgets(s->name,60,stdin);

    printf("=> 수정성공!\n");

    return 1;
}

void saveData(CCM *s[], int count){

    FILE *fp;
    char check[1] = "$";

    fp = fopen("CCM악보 모음집.txt", "wt");
    for(int i=0;i<count;i++){
        if(s[i] != NULL){
            fprintf(fp, "%s", 
            s[i]->name);
        }
    }
    fprintf(fp,"$",check);
    fclose(fp);
    printf("저장됨!");  
}

int loadData(CCM *s[]){
    int count = 0;
    FILE *fp;

    fp = fopen("CCM악보 모음집.txt", "rt");
    if(fp == NULL){
        printf("=> 파일 없음\n");
        return 0;
    }

 while(!feof(fp))  // 파일의 끝이 아니라면

   {
       s[count] = (CCM*)malloc(sizeof(CCM));
       fgets(s[count]->name, 60, fp);  
       if(!strcmp(s[count]->name,"$")) 
       {    free(s[count]);
            s[count]=NULL;
            break; 
       }
       count++;
   }
    fclose(fp);
    printf("=> 로딩 성공!\n");

    return count;
}

int selectMenu(){     
    int menu;
    printf("\n*** 악보 관리 프로그램 ***\n");
    printf("1. 조회\n");
    printf("2. 추가\n");
    printf("3. 수정\n");
    printf("4. 삭제\n");
    printf("5. 파일저장\n");
    printf("6. 검색\n");
    printf("0. 종료\n\n");
    printf("=> 원하는 메뉴는? ");
    while(1){
        if(scanf("%d", &menu)==0){
            printf("숫자를 입력하세요 : ");
            rewind(stdin);
            continue;
        }
        else{
            if(menu<0||menu>6){
                printf("올바른 번호를 입력하세요 : ");
            }
            else break;
        }
        
    }

    return menu;
}

int searchName(CCM *s[], int curi){
    int scount =0;
    char search[60];

    printf("\n검색할 이름(취소 : 0) : ");
    fgets(search,60,stdin);
    search[strlen(search)-1] = '\0';	

    if(strcmp(search, "0")==0) return 0;

    printf("\n No name\n");
    printf("===================================================\n");
    for(int i=0; i<curi; i++){
        if(s[i]!=NULL){
            if(strstr(s[i]->name, search)){
                printf("%3d ", i+1);
                readCCM(*s[i]);
                scount++;
            }
        }
    }
    if(scount==0) printf("=> 검색된 데이터 없음!\n");
    return 1;
}
