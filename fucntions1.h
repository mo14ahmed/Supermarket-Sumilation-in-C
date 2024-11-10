void printingfile();
void readfile();
void list();
void printmenu();
int removeitem();
void additem();
void buying();
int options();


// Creting the data strcuture to hold all the properties of the items
struct item{
	int barecode;
	char name[50];
    int quantity;
    float price;
    char production_date[50];
    char expiration_date[50];
    float offer;
    float priceafter;
	};
	
struct item stock[100]; // creating the struct array to hold the elements
int num_items = 0;

// this functions converts the string to date 
time_t convertToDate(char* dateStr)
{
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
	strptime(dateStr,"%Y-%m-%d",&tm);
    time_t t = mktime(&tm);
    return t;
}

// this fucntions reads the items from file
void readfile(){
	FILE *in;
	char line[100];
	in =fopen("stack", "r");
	int num=1;
	char holder[50];
	if (in){
while(fgets(line, 100, in)!=NULL){
    switch(num){
		case 1 :
		stock[num_items].barecode=atoi(line);
		num++;
		break;
		case 2 : //save in name
		strcpy(holder,line);
		holder[strlen(holder)-1]='\0';
		strcpy(stock[num_items].name,holder);
		num++;
		break;
		case 3 : // save in quanitity ;
		stock[num_items].quantity=atoi(line);
		num++;
		break; 
		case 4: //save the price
		stock[num_items].price=atoi(line);
		num++;
		break;
		case 5:
		strcpy(holder,line);
		holder[strlen(holder)-1]='\0';
		strcpy(stock[num_items].production_date,holder);
		num++;
		break;
		case 6:
		strcpy(holder,line);
		holder[strlen(holder)-1]='\0';
		strcpy(stock[num_items].expiration_date,holder);
		num=1;
		num_items++;
		break;
		}
    
	}
	fclose(in);	
	
}}
// this function prints the Main Menu	
void printmenu(){
	printf("\nMain Menu\n\t[1]Add Product\n\t[2]Remove Product\n\t[3]Display All products\n\t[4]Buy\n\t[5]Update Item\n\t[6]Exit.");
	printf("\n");
	}
	
// to remove item from the list 	
int removeitem(){
	printf("Enter the barcode of item you want to remove: ");
	int num=0; 
	scanf("%d", &num);
	
	for (int i =0; i<num_items; i++){
		if (stock[i].barecode==num){
			stock[i].barecode = 0;
			printf("%s has been removed succussefully !\n" , stock[i].name);
			return 0;
			}
		}
		printf("Enter a valid barcode");
		removeitem();
		return 0;
	}
// this to add a new item to the list 
void additem(){
		
		list();
        
		printf("Enter the items's barcode(Enter a non-existing barcode):");
		scanf("%d",&stock[num_items].barecode);
		
		printf("Enter the items's name:");
        scanf("%s",stock[num_items].name);		
        
		printf("Enter the items's quantity:");
		scanf("%d",&stock[num_items].quantity);		

		printf("Enter the items's price:");
		scanf("%f",&stock[num_items].price);		

		
		printf("Enter the items's production date in this form (yyyy/mm/dd):");
		scanf("%s",stock[num_items].production_date);		

		printf("Enter the items's expiration date in this form (yyyy/mm/dd):");
		scanf("%s",stock[num_items].expiration_date);		
         
        num_items++;
        list(); 
		
		}
// to print the whole list
void list(){
	printf("\n\033[0;31mBarcode\033[0;37m |\033[0;32mItem Name\033[0;37m             | \033[0;33mQuantity\033[0;37m    | \033[0;34mPrice\033[0;37m     | \033[0;35mProduction Date\033[0;37m | \033[0;36mExpiration date\n\033[0;37m");
	for (int i=0; i<num_items; i++){
		if (stock[i].barecode!=0){
		printf("\033[0;37m-----------------------------------------------------------------------------------------\n");
		printf("\033[0;31m%-7d\033[0;37m | \033[0;32m%-20s\033[0;37m | \033[0;33m%-3d\033[0;37m \t     | \033[0;34m%-5.1f\033[0;37m\t | \033[0;35m%s\033[0;37m\t   | \033[0;36m%s\033[0;37m\n",
		stock[i].barecode,stock[i].name,stock[i].quantity
		,stock[i].price,stock[i].production_date,stock[i].expiration_date );
		
		}}}
// to buy items from the list 
void buying(){
	char date1[50];
	printf("Enter today's date:");
	scanf("%s", date1);
    
 time_t t1 = convertToDate(date1);
 
     list();
	for (int i =0; i<num_items; i++){
	
     time_t t2 = convertToDate(stock[i].expiration_date);

    double diffSeconds = difftime(t2, t1);

    int days = (int)(diffSeconds / (60 * 60 * 24));
    
    if (diffSeconds<0){
		printf("%s is expired and deleted\n", stock[i].name);
		stock[i].offer=-1;
		}else {
    stock[i].offer=0.75/days;
    stock[i].priceafter=stock[i].price-(stock[i].price*stock[i].offer);
		}}
	printf("\n\033[0;31mBarcode\033[0;37m |\033[0;32mItem Name\033[0;37m             | \033[0;33mQuantity\033[0;37m    | \033[0;34mPrice\033[0;37m     | \033[0;35mProduction Date\033[0;37m | \033[0;36mExpiration date\033[0;37m    | Price after Offer\n");
	for (int i=0; i<num_items; i++){
		if (stock[i].barecode!=0 && stock[i].offer !=-1){
		printf("\033[0;37m----------------------------------------------------------------------------------------------------------\n");
		printf("\033[0;31m%-7d\033[0;37m | \033[0;32m%-20s\033[0;37m | \033[0;33m%-3d\033[0;37m \t     | \033[0;34m%-5.1f\033[0;37m\t | \033[0;35m%s\033[0;37m\t   | \033[0;36m%s\033[0;37m\t\t| \t%.2f\n",
		stock[i].barecode,stock[i].name,stock[i].quantity
		,stock[i].price,stock[i].production_date,stock[i].expiration_date, stock[i].priceafter);
		
		}}
		printf("\n");
		int search,quan,num=0;
		float reciept;
		char letter;
		char line3[50][25];
		printf("Type y to add items to your reciept or n to exit: ");
		scanf(" %c",&letter);
		while(letter=='y'){
		printf("Please enter the barcode of the item you want to add to the reciept: ");
		scanf("%d",&search);
		for(int i =0;i<num_items;i++){
			if(stock[i].barecode==search && stock[i].offer!=-1){
				printf("Enter the quantity needed: ");
				scanf("%d",&quan);
				if(quan>stock[i].quantity){
					printf("Sorry no available items");
					continue ;
					}else{
			reciept=reciept+(stock[i].priceafter*quan);
			stock[i].quantity=stock[i].quantity-quan ;
			strcat(line3[num], stock[i].name);
			num++;
			sprintf(line3[num],"%d",quan);
			num++;
			sprintf(line3[num],"%.2f",stock[i].priceafter*quan);
			num++;
			
			}
				}
			}
			printf("Type y to add items to your reciept or n to exit: ");
			scanf(" %c",&letter);
	}
	printf("---------------------------------------------------------\n");
	printf("The Reciept:\n");
	for (int i =0; i<num; i++){
		printf("%s \t", line3[i]);
		if ((i+1)%3==0){
		printf("\n");
		}
	}
	printf("---------------------------------------------------------\n");
	printf("\tTotal is %.2f\n", reciept);
	} 
int updateitem(){
	list();
	int num;
	printf("\nEnter the barcode of item to update: ");
	scanf("%d", &num);
	
	for (int i =0; i<num_items; i++){
		if (num==stock[i].barecode){
			printf("Enter the items's quantity:");
			scanf("%d",&stock[i].quantity);		

			printf("Enter the items's price:");
			scanf("%f",&stock[i].price);		

		
			printf("Enter the items's production date in this form (yyyy/mm/dd):");
			scanf("%s",stock[i].production_date);		

			printf("Enter the items's expiration date in this form (yyyy/mm/dd):");
			scanf("%s",stock[i].expiration_date);
			
			list();
			return 0;	
			}
		}
		printf("Enter a valid barcode !");
		return 0;
	}
	
int options(){
	int num; 
	printmenu();
	printf("Enter the Number of process you need: ");
	scanf("%d", &num);
	switch (num){
		case 1: 
		additem();
		options();
		break;
		case 2:
		removeitem();
		list();
		options();
		break;
		case 3:
		list();
		options();
		break;
		case 4: 
		buying();
		options();
		break;
		case 5:
		updateitem();
		options();
		break;
		case 6:
		printingfile();
		return 0;
		} return 0;}
void printingfile(){
	FILE *out; 
	out = fopen("Stock update.txt", "w");
	for (int i=0; i<num_items; i++){
		if (stock[i].barecode!=0){
		fprintf(out,"----------------------------------------------------------------------------------------------------------\n");
		fprintf(out,"%-7d | %-20s | %-3d \t     | %-5.1f | %s\t   | %s\t\t| \t%.2f\n",stock[i].barecode,stock[i].name,stock[i].quantity
		,stock[i].price,stock[i].production_date,stock[i].expiration_date, stock[i].priceafter);
		}}
	fclose(out);
	}
		
