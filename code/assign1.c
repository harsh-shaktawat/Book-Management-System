/*      ASSUMPTIONS
------> dates are considered within a single month from day1 to day15
------> return date = -1, indicates book is not returned till current date
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum{FAILURE,SUCCESS} status_code;
typedef enum{FALSE,TRUE} bool;
int CURRENT_DATE;
typedef struct bookNode_tag{
    char title[30];
    char author[30];
    char subject[30];
    int copies_issued;
    int copies_available;
    struct bookNode_tag* next;
}bookNode;
typedef struct bookList_tag{
    bookNode* front;
    bookNode* rear;
}bookList;
typedef struct requestNode_tag{
    char name[30];
    char bookTitle[30];
    struct requestNode_tag* next;
}requestNode;
typedef struct requestQueue_tag{
    requestNode* front;
    requestNode* rear;
}requestQueue;
typedef struct borrowNode_tag{
    char name[30];
    char title[30];
    int issueDate;
    int returnDate;
    struct borrowNode_tag* next; 
}borrowNode;
typedef struct borrowList_tag{
    borrowNode* front;
    borrowNode* rear;
}borrowList;
typedef struct freqNode_tag{
    char name[30];
    int count;
    struct freqNode_tag* next;
}freqNode;

void initializeBookList(bookList* bptr){
    bptr->front=NULL;
    bptr->rear=NULL;
}
bool isBookListEmpty(bookList* bptr){
    return (bptr->front==NULL && bptr->rear==NULL);
}
bookNode* createBookNode(char title[30],char author[30], char subject[30], int issued,int available){
    bookNode *nptr=(bookNode*) malloc(sizeof(bookNode));
    strcpy(nptr->title,title);
    strcpy(nptr->author,author);
    strcpy(nptr->subject,subject);
    nptr->copies_issued=issued;
    nptr->copies_available=available;
    nptr->next=NULL;
    return nptr;
}
status_code insertBook(bookList* lptr,bookNode* book){
    status_code ret_val=SUCCESS;
    if(book==NULL){
        ret_val=FAILURE;
    }
    else{
        if(isBookListEmpty(lptr)){
            lptr->front=lptr->rear=book;
        }
        else{
            (lptr->rear)->next=book;
            lptr->rear=book;
        }
    }   
    return ret_val;
}
void printBookList(bookNode* head){
    printf("\n--------BOOK LIST--------\n");
    while(head!=NULL){
        printf("%s\t%s\t%s\t%d\t%d\n",head->title,head->author,head->subject,head->copies_issued,head->copies_available);
        head=head->next;
    }
}
void createBookList(bookList* myBookList){
    int tot;
    printf("How many books you want to add\n");
    scanf("%d", &tot);
    bookList lptr=*myBookList;
    status_code ret_val;
    while(tot--){
        char title[30];
        char author[30];
        char subject[30];
        int issued,available;
        printf("Enter title of book\n");
        scanf("%s", title);
        printf("Enter author of book\n");
        scanf("%s", author);
        printf("Enter subject of book\n");
        scanf("%s", subject);
        printf("Enter no of issued copies\n");
        scanf("%d", &issued);
        printf("Enter no of books available\n");
        scanf("%d", &available);
        bookNode* newBook=createBookNode(title,author,subject,issued,available);
        ret_val=insertBook(&lptr,newBook);
    }
    *myBookList=lptr;
}

void initializeQueue(requestQueue* qptr){
    qptr->front=NULL;
    qptr->rear=NULL;
}
bool isRequestQueueEmpty(requestQueue* qptr){
    return (qptr->front==NULL && qptr->rear==NULL);
}
requestNode* createRequestNode(char name[30],char title[30]){
    requestNode* nptr=(requestNode*)malloc(sizeof(requestNode));
    strcpy(nptr->name,name);
    strcpy(nptr->bookTitle,title);
    nptr->next=NULL;
    return nptr;
}
status_code insertRequest(requestQueue* qptr,requestNode* request){
    status_code ret_val=SUCCESS;
    if(request==NULL){
        ret_val=FAILURE;
    }
    else{
        if(isRequestQueueEmpty(qptr)){
            qptr->front=qptr->rear=request;
        }
        else{
            (qptr->rear)->next=request;
            qptr->rear=request;
        }
        
    }
    return ret_val;
}
void printRequestQueue(requestNode* head){
    printf("\n--------REQUEST QUEUE--------\n");
    while(head!=NULL){
        printf("%s\t%s\n", head->name,head->bookTitle);
        head=head->next;
    }
}
void createRequestQueue(requestQueue* myQueue){
    int tot;
    printf("How many request you want to add\n");
    scanf("%d", &tot);
    requestQueue qptr=*myQueue;
    status_code ret_val;
    while(tot--){
        char name[30];
        char title[30];
        printf("Enter name of student\n");
        scanf("%s", name);
        printf("Enter title of book\n");
        scanf("%s", title);
        requestNode* newRequest=createRequestNode(name,title);
        ret_val=insertRequest(&qptr,newRequest);
    }
    *myQueue=qptr;
}

void initializeBorrowList(borrowList* bptr){
    bptr->front=NULL;
    bptr->rear=NULL;
}
bool isBorrowListEmpty(borrowList* bptr){
    return (bptr->front==NULL && bptr->rear==NULL);
}
borrowNode* createBorrowNode(char name[30],char title[30],int issuedate,int returndate){
    borrowNode* bptr=(borrowNode*)malloc(sizeof(borrowNode));
    strcpy(bptr->name,name);
    strcpy(bptr->title,title);
    bptr->issueDate=issuedate;
    bptr->returnDate=returndate;
    bptr->next=NULL;
    return bptr;
}
status_code insertBorrowNode(borrowList* bptr,borrowNode* borrow){
    status_code ret_val=SUCCESS;
    if(borrow==NULL){
        ret_val=FAILURE;
    }
    else{
        if(isBorrowListEmpty(bptr)){
            bptr->front=bptr->rear=borrow;
        }
        else{
            (bptr->rear)->next=borrow;
            bptr->rear=borrow;
        }
    }
    return ret_val;
}
void printBorrowList(borrowNode* head){
    printf("\n--------BORROW LIST--------\n");
    while(head!=NULL){
        printf("%s\t%s\t",head->name,head->title);
        printf("%d\t%d\n",head->issueDate,head->returnDate);
        head=head->next;
    }
}
void incrementBook(bookList myBookList,char title[30]){
    bookNode* ptr=myBookList.front;
    bool flag=1;
    while(ptr!=NULL && flag==1){
        if(strcmp(ptr->title,title)==0){
            ptr->copies_available++;
            ptr->copies_issued--;
            flag=0;
        }
        ptr=ptr->next;
    }
}
void returnBook(bookList myBookList,borrowList myBorrowList){
    borrowNode* ptr=myBorrowList.front;
    int retDate;
    char name[30];
    char title[30];
    printf("enter name of student\n");
    scanf("%s", name);
    printf("enter title of book\n");
    scanf("%s", title);
    printf("enter return date\n");
    scanf("%d", &retDate);
    bool found=FALSE;
    while(ptr!=NULL && found==FALSE){
        if(strcmp(ptr->name,name)==0 && strcmp(ptr->title,title)==0){
            found=TRUE;
        }
        else{
            ptr=ptr->next;
        }
    }
    if(found){
        ptr->returnDate=retDate;
        incrementBook(myBookList,title);
        printf("Return date updated\n");
    }
    else{
        printf("Invalid details\n");
    }
}

int countBorrowedBooks(borrowNode* borrowHead,char name[30]){
    int count=0;
    
    borrowNode* ptr=borrowHead;
    
    while(ptr!=NULL){
        if(strcmp(ptr->name,name)==0 && ptr->returnDate==-1){//return date -1 indicates book is not returned till current date
            count++;
        }
        ptr=ptr->next;
    }
    
    return count;
}
int countAvailableCopies(bookNode* bookHead,char title[30]){
    int cnt=0;
    bookNode* ptr=bookHead;
    bool found=0;
    
    while(ptr!=NULL && found==0){
        
        if(strcmp(ptr->title,title)==0){
            found=1;
        }else{
            ptr=ptr->next;
        }
        
    }
    if(found==1) cnt=ptr->copies_available;
    
    return cnt;
}
int daysGap(int day1,int day2){
    int count=0;
    count=day2-day1;
    return count;
}
bool isDefaulter(borrowNode* borrowHead,char name[30]){
    borrowNode* ptr=borrowHead;
    bool ret_val=FALSE;
    
    while(ptr!=NULL){
        if(strcmp(ptr->name,name)==0){
            int gap;
            if(ptr->returnDate!=-1){
                gap=daysGap(ptr->issueDate,ptr->returnDate);
            }
            else {
                gap=CURRENT_DATE-ptr->issueDate;
            }
            if(gap>15){
                ret_val=TRUE;
            }
        }
        
        ptr=ptr->next;
    }
    return ret_val;
}
status_code insertBorrowNode2(borrowNode** head,borrowNode* nptr){
    borrowNode* lptr;
    lptr=*head;
    if(lptr==NULL){
        lptr=nptr;
        *head=lptr;
    }
    else{
        borrowNode* ptr;
        ptr=lptr;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        ptr->next=nptr;
        *head=lptr;
    }
    return SUCCESS;
}
status_code insertRequest2(requestNode** head,requestNode* nptr){
    requestNode* lptr;
    lptr=*head;
    if(lptr==NULL){
        lptr=nptr;
        *head=lptr;
    }
    else{
        requestNode* ptr;
        ptr=lptr;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        ptr->next=nptr;
        *head=lptr;
    }
    return SUCCESS;
}
void decrementBook(bookNode* head,char title[30]){
    bookNode* ptr=head;
    while(ptr!=NULL){
        if(strcmp(ptr->title,title)==0){
            ptr->copies_available--;
            ptr->copies_issued++;
        }
        ptr=ptr->next;
    }
}
requestNode* deleteAfter(requestNode* p,requestNode* q,requestNode* lptr){
    if(q!=NULL){
        if(p!=NULL){
            if(p->next==q){
                p->next=q->next;
                free(q);
            }
        }
        else{
            if(q==lptr){
                lptr=lptr->next;
                free(q);
            }
        }
    }
    return lptr;
}

void q1(bookList* myBookList,requestQueue* myQueue,borrowList* myBorrowList){
    bookNode* ptr1=myBookList->front;
    requestNode* ptr2=myQueue->front;
    requestNode* prev=NULL;
    borrowNode* ptr3=myBorrowList->front;
    requestQueue newQueue;//new queue to store request who were shifted to last priortiy
    initializeQueue(&newQueue);
    printf("\nEnter date of issue(current date, must be between 1 to 15)\n");
    scanf("%d", &CURRENT_DATE);//date on which books are issued
    if(isRequestQueueEmpty(myQueue)){
        printf("Request queue is empty\n");
    }
    else{
        printf("\nProcessing request queue\n");
        while(ptr2!=NULL){
            printf("%s-----",ptr2->name);
            int cnt1=countBorrowedBooks(myBorrowList->front,ptr2->name);
            int cnt2=countAvailableCopies(myBookList->front,ptr2->bookTitle);
            if(cnt2==0){
                printf("PENDING: All copies are issued. Book is not avilable\n");
                prev=ptr2;//store current node in prev bcoz in future the copy might be available
                ptr2=ptr2->next;
            }
            else{
                if(cnt1==0){//cnt==0 indicates no book is issued by student
                    printf("SUCCESS\n");
                    borrowNode* newNode=createBorrowNode(ptr2->name,ptr2->bookTitle,CURRENT_DATE,-1);
                    status_code val= insertBorrowNode(myBorrowList,newNode);//insert node in borrowlist
                    decrementBook(myBookList->front,ptr2->bookTitle);//decrement book from booklist
                }
                else if(cnt1<3){
                    if(isDefaulter(myBorrowList->front,ptr2->name)){
                        printf("FAILURE:Previous book not returned on time(DEFAULTER)\n");
                    }
                    else{
                        printf("already borrowed book. Moving the request to lowest priority\n");
                        requestNode* newNode=createRequestNode(ptr2->name,ptr2->bookTitle);
                        status_code val=insertRequest(&newQueue,newNode);//moving the request into new queue for later proccessing
                    }
                }
                else if(cnt1>=3){
                    printf("FAILURE: Already 3 books borrowed\n");
                }
                requestNode* toDelete=ptr2;//current node is proccessed so delete it
                ptr2=ptr2->next;
                myQueue->front=deleteAfter(prev,toDelete,myQueue->front);
            }
            
        }
        ptr2=newQueue.front;
        if(ptr2!=NULL){
            printf("\nProcesssing request of students who were shifted to lowest priority\n");
            while(ptr2!=NULL){
                printf("%s-----",ptr2->name);
                int cnt1=countBorrowedBooks(myBorrowList->front,ptr2->name);
                int cnt2=countAvailableCopies(myBookList->front,ptr2->bookTitle);
                if(cnt1==0){
                    requestNode* newNode=createRequestNode(ptr2->name,ptr2->bookTitle);
                    status_code ret_val=insertRequest(myQueue,newNode);//insert request to original queue bcoz in future it might be available
                    printf("PENDING: All copies are issued. Book is not avilable\n");
                }
                else{
                    if(cnt1<3){
                        printf("SUCCESS\n");
                        borrowNode* newNode=createBorrowNode(ptr2->name,ptr2->bookTitle,CURRENT_DATE,-1);
                        status_code val= insertBorrowNode(myBorrowList,newNode);
                        decrementBook(myBookList->front,ptr2->bookTitle);
                    }
                    else{
                        printf("FAILURE: Already 3 books borrowed\n");
                    }
                    
                }
                ptr2=ptr2->next;
            }
        }
        if(myQueue->front==NULL){
            initializeQueue(myQueue);
        }
    }
    
}

int countBooks(requestNode* queueHead,char title[30]){
    int cnt=0;
    requestNode* ptr2=queueHead;
    while(ptr2!=NULL){
            if(strcmp(ptr2->bookTitle,title)==0){
                cnt++;
            }
            ptr2=ptr2->next;
    }
    return cnt;
}
void q2(bookNode* bookHead,requestNode* queueHead,borrowNode* borrowHead){
    bookNode* ptr1=bookHead;
    char bookName[30];
    int ans=-1;
    if(ptr1==NULL){
        printf("Book list is empty\n");
    }
    else{
        while(ptr1!=NULL){
            int count=ptr1->copies_issued+countBooks(queueHead,ptr1->title);
            if(count>ans){
                ans=count;
            }
            ptr1=ptr1->next;
        }
        printf("\nBooks in most demand:\n", bookName);
        ptr1=bookHead;
        while(ptr1!=NULL){
            int count=ptr1->copies_issued+countBooks(queueHead,ptr1->title);
            if(count==ans){
                printf("%s\n",ptr1->title);
            }
            ptr1=ptr1->next;
        }
    }
    
}

void q3(bookNode* bookHead,borrowNode* borrowHead){
    bookNode* ptr1=bookHead;
    borrowNode* ptr2=borrowHead;
    int stDay;
    printf("\nEnter starting day\n");
    scanf("%d", &stDay);
    int range=stDay+3;
    if(ptr1==NULL){
        printf("Book list is empty\n");
    }
    else{
        while(ptr1!=NULL){
            int tot=(ptr1->copies_available)+(ptr1->copies_issued);
            ptr2=borrowHead;
            while(ptr2!=NULL){
                if(strcmp(ptr2->title,ptr1->title)==0 ){
                    if(ptr2->returnDate==-1) tot--;
                    else if(stDay<=(ptr2->issueDate) && (ptr2->issueDate)<range && (ptr2->returnDate>range)){
                        tot--;
                    }
                }
                ptr2=ptr2->next;
            }
            printf("%d books of title %s can be given\n",tot,ptr1->title);
            ptr1=ptr1->next;
        }
    }
    
}

freqNode* DivideF(freqNode* lptr){
    freqNode* nptr,*fast,*slow;
    slow=lptr;
    fast=lptr->next->next;
    while(fast!=NULL){
        fast=fast->next;
        slow=slow->next;
        if(fast!=NULL){
            fast=fast->next;
        }
    }
    nptr=slow->next;
    slow->next=NULL;
    return nptr;
}
freqNode* MergeF(freqNode* lptr,freqNode* nptr){
    freqNode* ptr1,*ptr2,*result,*tail;
    ptr1=lptr;
    ptr2=nptr;
    if((ptr1->count)>ptr2->count){
        result=ptr1;
        ptr1=ptr1->next;
    }
    else{
        result=ptr2;
        ptr2=ptr2->next;
    }
    tail=result;
    while((ptr2!=NULL) && (ptr1!=NULL)){
        if((ptr1->count)>(ptr2->count)){
            tail=tail->next=ptr1;
            ptr1=ptr1->next;
        }
        else{
            tail=tail->next=ptr2;
            ptr2=ptr2->next;
        }
    }
    if(ptr1!=NULL) tail->next=ptr1;
    else tail->next=ptr2;
    return result;
}
freqNode* MergeSortF(freqNode* list_ptr){
    freqNode* lptr,*nptr;
    lptr=list_ptr;
    if((lptr!=NULL) && (lptr->next!=NULL)){
        nptr=DivideF(lptr);
        lptr=MergeSortF(lptr);
        nptr=MergeSortF(nptr);
        lptr=MergeF(lptr,nptr);
    }
    return lptr;
}

bookNode* Divide(bookNode* lptr){
    bookNode* nptr,*fast,*slow;
    slow=lptr;
    fast=lptr->next->next;
    while(fast!=NULL){
        fast=fast->next;
        slow=slow->next;
        if(fast!=NULL){
            fast=fast->next;
        }
    }
    nptr=slow->next;
    slow->next=NULL;
    return nptr;
}
bookNode* Merge(bookNode* lptr,bookNode* nptr){
    bookNode* ptr1,*ptr2,*result,*tail;
    ptr1=lptr;
    ptr2=nptr;
    if((ptr1->copies_issued)>ptr2->copies_issued){
        result=ptr1;
        ptr1=ptr1->next;
    }
    else{
        result=ptr2;
        ptr2=ptr2->next;
    }
    tail=result;
    while((ptr2!=NULL) && (ptr1!=NULL)){
        if((ptr1->copies_issued)>(ptr2->copies_issued)){
            tail=tail->next=ptr1;
            ptr1=ptr1->next;
        }
        else{
            tail=tail->next=ptr2;
            ptr2=ptr2->next;
        }
    }
    if(ptr1!=NULL) tail->next=ptr1;
    else tail->next=ptr2;
    return result;
}
bookNode* MergeSort(bookNode* list_ptr){
    bookNode* lptr,*nptr;
    lptr=list_ptr;
    if((lptr!=NULL) && (lptr->next!=NULL)){
        nptr=Divide(lptr);
        lptr=MergeSort(lptr);
        nptr=MergeSort(nptr);
        lptr=Merge(lptr,nptr);
    }
    return lptr;
}
int count(requestNode* queueHead,char name[30]){
    requestNode* ptr=queueHead;
    int count=1;
    while(ptr!=NULL){
        if(strcmp(ptr->name,name)==0){
            count++;
        }
        ptr=ptr->next;
    }
    return count;    
}
bool isPresent(freqNode* head,char name[30]){
    freqNode* ptr1=head;
    bool ret_val=FALSE;

    while(ptr1!=NULL && ret_val==FALSE){
        if(strcmp(ptr1->name,name)==0){
            ret_val=TRUE;
        }
        ptr1=ptr1->next;
    }
    return ret_val;
}
freqNode* createFreqNode(char name[30],int cnt ){
    freqNode* newNode=(freqNode*)malloc(sizeof(freqNode));
    strcpy(newNode->name,name);
    newNode->count=cnt;
    newNode->next=NULL;
    return newNode;
}
freqNode* insertFreqNode(freqNode* lptr,freqNode* ptr){
    if(lptr==NULL){
        lptr=ptr;
    }
    else{
        freqNode* nptr=lptr;
        while(nptr->next!=NULL){
            nptr=nptr->next;
        }
        nptr->next=ptr;
    }
    return lptr;
}
void q4(borrowNode* borrowHead){
    freqNode* head=NULL;
    borrowNode* ptr=borrowHead;
    if(ptr==NULL){
        printf("Borrower list is empty\n");
    }
    else{
        while(ptr!=NULL){
            int cnt=countBorrowedBooks(borrowHead,ptr->name);
            if(isPresent(head,ptr->name)==FALSE && cnt!=0){
                head=insertFreqNode(head,createFreqNode(ptr->name,cnt));
            }
            ptr=ptr->next;
        }
        head=MergeSortF(head);
        freqNode* ptr1=head;
        printf("\nSorted borrower_list according to the number of books issued in descending order\n");
        while(ptr1!=NULL){
            printf("%s\n",ptr1->name,ptr1->count);
            ptr1=ptr1->next;
        }
    }
    
}

void q5(bookNode* bookHead){
    char sub[30];
    printf("\nEnter the subject of books\n");
    scanf("%s", sub);
    bookNode* ptr=bookHead;
    bookList tempList;
    initializeBookList(&tempList);
    if(ptr==NULL){
        printf("Book list is empty\n");
    }
    else{
        while(ptr!=NULL){
            if(strcmp(ptr->subject,sub)==0){
                bookNode* newNode=createBookNode(ptr->title,ptr->author,ptr->subject,ptr->copies_issued,ptr->copies_available);
                status_code ret_val=insertBook(&tempList,newNode);
            }
            ptr=ptr->next;
        }
        
        tempList.front =MergeSort(tempList.front);
        //printBookList(tempList.front);
        ptr=tempList.front;
        printf("\nBooks with subject %s:\n", sub);
        printf("\n     AUTHOR\tTITLE\n\n");
        while(ptr!=NULL){
            printf("---->%s\t%s\n",ptr->author,ptr->title);
            ptr=ptr->next;
        }
    }
    
}

bool isDefaulterPresent(requestNode* defaulterHead,char name[30]){
    bool ret_val=FALSE;
    requestNode* ptr=defaulterHead;
    while(ptr!=NULL && ret_val==FALSE){
        if(strcmp(ptr->name,name)==0)
        {
            ret_val=TRUE;
        }
        ptr=ptr->next;
    }
    return ret_val;
}
void q6(requestNode* queueHead,borrowNode* borrowHead){
    requestQueue defaulter_list;
    initializeQueue(&defaulter_list);
    requestNode* ptr=queueHead;
    requestNode* prev=NULL;
    if(ptr==NULL){
        printf("Request queue is empty\n");
    }
    else{
        while(ptr!=NULL){
            if(isDefaulter(borrowHead,ptr->name)){
                requestNode* newNode=createRequestNode(ptr->name,ptr->bookTitle);
                if(isDefaulterPresent(defaulter_list.front,ptr->name)==FALSE) insertRequest(&defaulter_list,newNode);
                requestNode* toDelete=ptr;
                ptr=ptr->next;
                queueHead=deleteAfter(prev,toDelete,queueHead);
            }
            else{
                prev=ptr;
                ptr=ptr->next;
            }
        }
        printf("\nNew request queue after deleting defaulters\n");
        printRequestQueue(queueHead);
        ptr=defaulter_list.front;
        printf("\nDEFAULTER LIST\n");
        while(ptr!=NULL){
            printf("%s\n",ptr->name);
            ptr=ptr->next;
        }
    }
    
}

void q7(requestNode* queueHead,borrowNode* borrowHead){
    requestNode* ptr=queueHead;
    borrowNode* ptr2;
    requestQueue list;
    initializeQueue(&list);
    if(ptr==NULL){
        printf("Request queue is empty\n");
    }
    else{
        while(ptr!=NULL){
            if(countBorrowedBooks(borrowHead,ptr->name)>0){
                requestNode* newNode=createRequestNode(ptr->name,ptr->bookTitle);
                if(isDefaulterPresent(list.front,ptr->name)==FALSE) insertRequest(&list,newNode);
            }
            ptr=ptr->next;
        }
        ptr=list.front;
        printf("\nName of students who already borrowed books and asking for other\n");
        while(ptr!=NULL){
            printf("%s\n",ptr->name);
            ptr=ptr->next;
        }
    }
    
}

void q8(bookNode* bookHead,requestNode* queueHead){
    requestNode* ptr=queueHead;
    if(ptr==NULL){
        printf("request queue is empty\n");
    }
    else{
        printf("\nName of requested books whose copies are available\n");
        while(ptr!=NULL){
            if(countAvailableCopies(bookHead,ptr->bookTitle)>0){
                printf("%s\n",ptr->bookTitle);
            }
            ptr=ptr->next;
        }
    }
    
}

void q9(bookNode* bookHead){
    bookNode* ptr=bookHead;
    if(ptr==NULL){
        printf("book list is empty\n");
    }
    else{
        printf("\nTitle of all the books which have not been issued by anyone\n");
        while(ptr!=NULL){
            if(ptr->copies_issued==0){
                printf("%s\n",ptr->title);
            }
            ptr=ptr->next;
        }
    }
    
}

void q10(requestNode* queueHead){
    requestNode* ptr=queueHead;
    requestNode* ptr2;
    int mx=-1;
    if(ptr==NULL){
        printf("request queue is empty\n");
    }
    else{
        while(ptr!=NULL){
            int k=(count(ptr->next,ptr->name));
            if(k>mx){
                mx=k;
            }
            ptr=ptr->next;
        }
        ptr=queueHead;
        printf("\nName of the student/s who has requested for the maximum number of books\n");
        while(ptr!=NULL){
            if(mx==count(ptr->next,ptr->name)){
                printf("%s\n",ptr->name);
            }
            ptr=ptr->next;
        }
    }
    
}

void questions(bookList* myBookList,requestQueue* myQueue,borrowList* myBorrowList){
    int opt;
    printf("\nPress\n1 for q1\n2 for q2\n3 for q3\n4 for q4\n");
    printf("5 for q5\n6 for q6\n7 for q7\n8 for q8\n");
    printf("9 for q9\n10 for q10\n");
    scanf("%d", &opt);
    if(opt==1){
        q1(myBookList,myQueue,myBorrowList);
    }
    else if(opt==2){  
        q2(myBookList->front,myQueue->front,myBorrowList->front);
    }
    else if(opt==3){
        q3(myBookList->front,myBorrowList->front);
    }
    else if(opt==4){
        q4(myBorrowList->front);
    }
    else if(opt==5){
        q5(myBookList->front);
    }
    else if(opt==6){
        q6(myQueue->front,myBorrowList->front);
    }
    else if(opt==7){
        q7(myQueue->front,myBorrowList->front);
    }
    else if(opt==8){
        q8(myBookList->front,myQueue->front);
    }
    else if(opt==9){
        q9(myBookList->front);
    }
    else if(opt==10){
        q10(myQueue->front);
    }
    else{
        printf("INVALID OPTION\n");
    }
}

int main(){
    bookList myBookList; 
    initializeBookList(&myBookList); 

    requestQueue myQueue; 
    initializeQueue(&myQueue); 
    
    borrowList myBorrowList; 
    initializeBorrowList(&myBorrowList); 

    char choice='y';
    while(choice=='y'){
        int opt;
        printf("\nPress\n0 to exit\n1 to insert book\n2 to display book list\n");
        printf("3 to insert request\n4 to display request queue\n5 to return book\n");
        printf("6 to display borrower list\n7 to display assignment questions\n");
        scanf("%d", &opt);
        if(opt==0){
            printf("\nEXITED\n");
            choice='n';
        }
        else if(opt==1){  
            createBookList(&myBookList);
        }
        else if(opt==2){
            printBookList(myBookList.front);
        }
        else if(opt==3){
            createRequestQueue(&myQueue);
        }
        else if(opt==4){
            printRequestQueue(myQueue.front);
        }
        else if(opt==5){
            returnBook(myBookList,myBorrowList);
        }
        else if(opt==6){
            printBorrowList(myBorrowList.front);
        }
        else if(opt==7){
            questions(&myBookList,&myQueue,&myBorrowList);
        }
        else{
            printf("Invalid option\nPress again\n");
        }
    }
    return 0;
}
