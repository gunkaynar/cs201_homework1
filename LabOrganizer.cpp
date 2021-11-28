#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
#include "LabOrganizer.h"


LabOrganizer::LabOrganizer(){
    size = 0;
    chemical_number = 0;
    if (size<=0){
        ids = NULL;
        rows_array= NULL;
        column_array= NULL;

    }

    else{
        ids = new int[ size ];
        rows_array = new int[size];
        column_array = new int[size];

    }
    if(chemical_number<=0){
        chemical_ids = NULL;
        chemical_cabinet_ids = NULL;
        chemical_rows= NULL;
        chemical_columns= NULL;
        chemical_type= NULL;
    }
    else{
        chemical_ids = new int[chemical_number];
        chemical_cabinet_ids= new int[chemical_number];
        chemical_rows= new int[chemical_number];
        chemical_columns= new int[chemical_number];
        chemical_type= new int[chemical_number];
    }
}

LabOrganizer::~LabOrganizer(){
    if ( ids ){
        delete [] ids;
    }
    if (rows_array){
        delete [] rows_array;
    }
    if (column_array){
        delete [] column_array;
    }
    if (chemical_ids){
        delete [] chemical_ids;
    }
    if (chemical_cabinet_ids){
        delete [] chemical_cabinet_ids;
    }
    if (chemical_rows){
        delete [] chemical_rows;
    }
    if (chemical_columns){
        delete [] chemical_columns;
    }
    if (chemical_type){
        delete [] chemical_type;
    }
}

void LabOrganizer::addCabinet(int id, int rows,int columns){
    int unique = 1;

    for(int i =0;i<size;i++){
        if (ids[i] == id){
            cout << "Cannot add the cabinet: ID "<< id << " already in the system" << endl;
            unique =0;
            break;
        }
    }
    if (unique ==1){
        if (rows > 9 || columns > 9){
            cout << "Cannot add the cabinet: dimensions are out of bounds" << endl;
        }
        else{
            int* deepCopy = new int[size];
            int* deepCopy2 = new int[size];
            int* deepCopy3 = new int[size];

            for(int i = 0; i < size; ++i){
                deepCopy[i] = ids[i];
                deepCopy2[i] = rows_array[i];
                deepCopy3[i] = column_array[i];
            }
            delete [] ids;
            delete [] rows_array;
            delete [] column_array;
            size++;

            ids = new int[ size ];
            rows_array = new int[ size ];
            column_array = new int[ size ];

            for ( int i = 0; i < size-1; i++ ){
                ids[ i ] = deepCopy[i];
                rows_array[ i ] = deepCopy2[i];
                column_array[ i ] = deepCopy3[i];
            }
            ids[size-1] = id;
            rows_array[size-1] = rows;
            column_array[size-1] = columns;
            delete [] deepCopy;
            delete [] deepCopy2;
            delete [] deepCopy3;

            cout << "Added a cabinet: ID " << id << " and dimensions "<<rows << " to " <<columns << endl;
        
        

        }
    
    }

}

void LabOrganizer::listCabinets(){
    if(size>0){
        cout << "List of all cabinets: "<< endl;
        for(int i=0;i<size;i++){
            int full =0;
            for(int j=0;j<chemical_number;j++){
                if(chemical_cabinet_ids[j]==ids[i]){
                    full++;
                }
            }
            cout << "ID: "<< ids[i] << ", Dim: " << rows_array[i] <<"x"<<column_array[i]<<", number of empty slots: " << rows_array[i]*column_array[i]-full<<endl;
        }
    }
}

    
    
    


void LabOrganizer::removeCabinet(int id){
    int exists = 0;
    int index=-1;
    for(int i = 0; i<size;i++){
        if (ids[i]==id){
            exists = 1;
            index = i;
            break;
        }
    }
    if (exists == 0){
        cout << "Cabinet " << id<< " does not exist in the system" << endl;
    }
    else{
        for (int k =0;k<chemical_number;){
            if(chemical_cabinet_ids[k]==id){
                cout << "Chemical " << chemical_ids[k] << " removed from cabinet "<< id<< endl;
                removeChemical(chemical_ids[k],1);

            }
            else{
                k++;
            }
        }
        int* deepCopy = new int[size];
        int* deepCopy2 = new int[size];
        int* deepCopy3 = new int[size];

        for(int i = 0; i < size; ++i){
            deepCopy[i] = ids[i];
            deepCopy2[i] = rows_array[i];
            deepCopy3[i] = column_array[i];
        }
        delete [] ids;
        delete [] rows_array;
        delete [] column_array;
        size--;
        
        
        ids = new int[ size ];
        rows_array = new int[ size ];
        column_array = new int[ size ];
        for (int i = 0; i < index; i++) {
            ids[ i ] = deepCopy[i];
            rows_array[ i ] = deepCopy2[i];
            column_array[ i ] = deepCopy3[i];
        }
        for (int i = index + 1; i < size+1; i++) {
            ids[ i -1] = deepCopy[i];
            rows_array[ i -1] = deepCopy2[i];
            column_array[ i -1] = deepCopy3[i];
            
        }
    delete [] deepCopy;
    delete [] deepCopy2;
    delete [] deepCopy3;
    cout << "Cabinet "<< id << " has been removed"<< endl;

    }

}




void LabOrganizer::findPlace(int cabinetId, int rows, int columns, int type,int chemID){
    int index=-1;
    for(int i=0;i<size;i++){
        if(cabinetId==ids[i]){
            index = i;
            break;
        }
    }
    int min = 20;
    int combustive_placable = 1;
    for (int i =0;i<rows_array[index];i++){
        for(int j=0;j<column_array[index];j++){
            int full = 0;
            for(int k=0;k<chemical_number;k++){
                if (chemical_cabinet_ids[k] ==cabinetId && chemical_rows[k]==i && chemical_columns[k]== j){
                    full = 1;
                    break;
                }
            }
            if(full==0){
                if(type ==1){
                    combustive_placable = combustivePlacable(type, cabinetId, i, j);
                    if(combustive_placable){
                        int difference_row = abs(rows-i);
                        int difference_column = abs(columns-j);
                        int difference = max(difference_row,difference_column);
                        if(difference <= min){
                            min = difference;
                        }

                    }
                }
                else{
                    int difference_row = abs(rows-i);
                    int difference_column = abs(columns-j);
                    int difference = max(difference_row,difference_column);
                    if(difference <= min){
                        min = difference;
                    }
                }

            }
            
            
        }
    }
    cout << " Nearest possible locations for this chemical: ";
    for (int i =0;i<rows_array[index];i++){
        for(int j=0;j<column_array[index];j++){
            int full = 0;
            for(int k=0;k<chemical_number;k++){
                if (chemical_cabinet_ids[k] ==cabinetId && chemical_rows[k]==i && chemical_columns[k]== j){
                    full = 1;
                    break;
                }
            }
            if(full==0){
                if(type ==1){
                    combustive_placable = combustivePlacable(type, cabinetId, i, j);
                    if(combustive_placable){
                        int difference_row = abs(rows-i);
                        int difference_column = abs(columns-j);
                        int difference = max(difference_row,difference_column);
                        if(difference==min){
                            char location[2];
                            if(i==0){
                                location[0] = 'A';
                            }
                            else if(i==1){
                                location[0] = 'B';
                            }
                            else if(i==2){
                                location[0] = 'C';
                            }
                            else if(i==3){
                                location[0] = 'D';
                            }
                            else if(i==4){
                                location[0] = 'E';
                            }
                            else if(i==5){
                                location[0] = 'F';
                            }
                            else if(i==6){
                                location[0] = 'G';
                            }
                            else if(i==7){
                                location[0] = 'H';
                            }
                            else if(i==8){
                                location[0] = 'I';
                            }
                            if(j==0){
                                location[1] = '1';
                            }
                            else if(j==1){
                                location[1] = '2';
                            }
                            else if(j==2){
                                location[1] = '3';
                            }
                            else if(j==3){
                                location[1] = '4';
                            }
                            else if(j==4){
                                location[1] = '5';
                            }
                            else if(j==5){
                                location[1] = '6';
                            }
                            else if(j==6){
                                location[1] = '7';
                            }
                            else if(j==7){
                                location[1] = '8';
                            }
                            else if(j==8){
                                location[1] = '9';
                            }
                            cout << location << ", ";
                        }
                    }
                }
                else{
                    int difference_row = abs(rows-i);
                    int difference_column = abs(columns-j);
                    int difference = max(difference_row,difference_column);
                    if(difference==min){
                        char location[2];
                        if(i==0){
                            location[0] = 'A';
                        }
                        else if(i==1){
                            location[0] = 'B';
                        }
                        else if(i==2){
                            location[0] = 'C';
                        }
                        else if(i==3){
                            location[0] = 'D';
                        }
                        else if(i==4){
                            location[0] = 'E';
                        }
                        else if(i==5){
                            location[0] = 'F';
                        }
                        else if(i==6){
                            location[0] = 'G';
                        }
                        else if(i==7){
                            location[0] = 'H';
                        }
                        else if(i==8){
                            location[0] = 'I';
                        }
                        if(j==0){
                            location[1] = '1';
                        }
                        else if(j==1){
                            location[1] = '2';
                        }
                        else if(j==2){
                            location[1] = '3';
                        }
                        else if(j==3){
                            location[1] = '4';
                        }
                        else if(j==4){
                            location[1] = '5';
                        }
                        else if(j==5){
                            location[1] = '6';
                        }
                        else if(j==6){
                            location[1] = '7';
                        }
                        else if(j==7){
                            location[1] = '8';
                        }
                        else if(j==8){
                            location[1] = '9';
                        }
                        cout << location << ", ";
                }
                }
            
        }
    }
    }
    cout << endl;

}
            
            
            
        


int LabOrganizer::combustivePlacable(int type, int cabinetId, int row, int column){
    for(int i = 0; i<chemical_number;i++){
        if(chemical_cabinet_ids[i]==cabinetId && chemical_type[i]==1){
            if(row==chemical_rows[i]){
                if(column-1==chemical_columns[i]){
                    return 0;
                }
                else if(column+1==chemical_columns[i]){
                    return 0;
                }
            }
            else if(column==chemical_columns[i]){
                if(row-1==chemical_rows[i]){
                    return 0;

                }
                else if(row+1==chemical_rows[i]){
                    return 0;

                }
            }
            else{
                if(column+1==chemical_columns[i]&&row+1==chemical_rows[i]){
                    return 0;

                }
                else if(column-1==chemical_columns[i]&&row+1==chemical_rows[i]){
                    return 0;

                }
                else if(column+1==chemical_columns[i]&&row-1==chemical_rows[i]){
                    return 0;

                }
                else if(column-1==chemical_columns[i]&&row-1==chemical_rows[i]){
                    return 0;

                }
            }
        }
        
        
    }
    return 1;
    
}


void LabOrganizer::placeChemical(int cabinetId, string location, string chemType, int chemID){
    char new_row = location[0];
    char new_column = location[1];
    int row = -1;
    int column = -1;
    if(new_row=='A'){
        row = 0;
    }
    else if(new_row=='B'){
        row = 1;
    }
    else if(new_row=='C'){
        row = 2;
    }
    else if(new_row=='D'){
        row = 3;
    }
    else if(new_row=='E'){
        row = 4;
    }
    else if(new_row=='F'){
        row = 5;
    }
    else if(new_row=='G'){
        row = 6;
    }
    else if(new_row=='H'){
        row = 7;
    }
    else if(new_row=='I'){
        row = 8;
    }
    if(new_column=='1'){
        column = 0;
    }
    else if(new_column=='2'){
        column = 1;
    }
    else if(new_column=='3'){
        column = 2;
    }
    else if(new_column=='4'){
        column = 3;
    }
    else if(new_column=='5'){
        column = 4;
    }
    else if(new_column=='6'){
        column = 5;
    }
    else if(new_column=='7'){
        column = 6;
    }
    else if(new_column=='8'){
        column = 7;
    }
    else if(new_column=='9'){
        column = 8;
    }
    
    int type = 0;
    if (chemType=="combustive"){
        type = 1;
    }
    
    
    
    int unique = 1;
    int no_place = 0;
    int combustive_placable = 1;

    
    for (int i =0;i<chemical_number;i++){
        if(chemical_ids[i]== chemID){
            unique = 0;
            cout << "Chemical with ID "<< chemID << " already exists in the system" << endl;
            break;
        }
    }
    for(int i = 0;i<chemical_number;i++){
        if(chemical_cabinet_ids[i]==cabinetId && chemical_rows[i]==row && chemical_columns[i] == column){
            no_place = 1;
            cout << "Location " << location << " in cabinet "<< cabinetId << " is already occupied." ;
            findPlace(cabinetId,  row,  column,  type,  chemID);
            break;
        }
    }
    
    if (unique==1 && no_place==0 && type == 1){
        combustive_placable = combustivePlacable(type, cabinetId, row, column);
    }
    if(combustive_placable==0){
        cout << "Location "<< location<< " in cabinet "<<cabinetId << " is not suitable for combustive chemicals." ;
        findPlace(cabinetId, row, column, 1, chemID);
    }
    if(unique==1 && no_place==0 && combustive_placable == 1){
        int* deepCopy = new int[chemical_number];
        int* deepCopy2 = new int[chemical_number];
        int* deepCopy3 = new int[chemical_number];
        int* deepCopy4 = new int[chemical_number];
        int* deepCopy5 = new int[chemical_number];

        for(int i = 0; i < chemical_number; ++i){
            deepCopy[i] = chemical_ids[i];
            deepCopy2[i] = chemical_cabinet_ids[i];
            deepCopy3[i] = chemical_rows[i];
            deepCopy4[i] = chemical_columns[i];
            deepCopy5[i] = chemical_type[i];

        }

        delete [] chemical_ids;
        delete [] chemical_cabinet_ids;
        delete [] chemical_rows;
        delete [] chemical_columns;
        delete [] chemical_type;

        chemical_number++;

        chemical_ids = new int[ chemical_number ];
        chemical_cabinet_ids = new int[ chemical_number ];
        chemical_rows = new int[ chemical_number ];
        chemical_columns = new int[ chemical_number ];
        chemical_type = new int[ chemical_number ];

        for ( int i = 0; i < chemical_number-1; i++ ){
            chemical_ids[ i ] = deepCopy[i];
            chemical_cabinet_ids[ i ] = deepCopy2[i];
            chemical_rows[ i ] = deepCopy3[i];
            chemical_columns[ i ] = deepCopy4[i];
            chemical_type[ i ] = deepCopy5[i];

        }
        chemical_ids[chemical_number-1] = chemID;
        chemical_cabinet_ids[chemical_number-1] = cabinetId;
        chemical_rows[chemical_number-1] = row;
        chemical_columns[chemical_number-1] = column;
        chemical_type[chemical_number-1] = type;

        delete [] deepCopy;
        delete [] deepCopy2;
        delete [] deepCopy3;
        delete [] deepCopy4;
        delete [] deepCopy5;
        if (type == 1){
            cout <<"Combustive chemical with ID " << chemID << " has been placed at location "<< location << " in cabinet " << cabinetId << endl;

        }
        else{
            cout <<"Retardant chemical with ID " << chemID << " has been placed at location "<< location << " in cabinet " << cabinetId << endl;
        }
    }
                
        
    
}

void LabOrganizer::findChemical(int id){
    int index = -1;
    for(int i=0;i<chemical_number;i++){
        if(chemical_ids[i]==id){
            index = i;
            break;
        }
    }
    if(index== -1){
        cout << "Chemical " << id << " is not in the system" << endl;
    }
    else{
        char location[2];
        int row = chemical_rows[index];
        int column = chemical_columns[index];
        if(row==0){
            location[0] = 'A';
        }
        else if(row==1){
            location[0] = 'B';
        }
        else if(row==2){
            location[0] = 'C';
        }
        else if(row==3){
            location[0] = 'D';
        }
        else if(row==4){
            location[0] = 'E';
        }
        else if(row==5){
            location[0] = 'F';
        }
        else if(row==6){
            location[0] = 'G';
        }
        else if(row==7){
            location[0] = 'H';
        }
        else if(row==8){
            location[0] = 'I';
        }
        if(column==0){
            location[1] = '1';
        }
        else if(column==1){
            location[1] = '2';
        }
        else if(column==2){
            location[1] = '3';
        }
        else if(column==3){
            location[1] = '4';
        }
        else if(column==4){
            location[1] = '5';
        }
        else if(column==5){
            location[1] = '6';
        }
        else if(column==6){
            location[1] = '7';
        }
        else if(column==7){
            location[1] = '8';
        }
        else if(column==8){
            location[1] = '9';
        }
    
    cout << "Chemical "<< id << " is at location "<< location << " in cabinet " << chemical_cabinet_ids[index]<< endl;
    }
}


void LabOrganizer::cabinetContents(int id){
    int index=-1;
    for (int j = 0;j<size;j++){
        if(ids[j]==id){
            index = j;
            break;
        }
        
    }
    if(index!=-1){
        char row_names [9] = {'A','B','C','D','E','F','G','H','I'};
        char column_names [9] = {'1','2','3','4','5','6','7','8','9'};
        int rows = rows_array[index];
        int columns = column_array[index];
        int c_this_turn =0;
        int r_this_turn =0;
        

        int full = 0;
        for(int i =0; i<chemical_number;i++){
         if(chemical_cabinet_ids[i]==id){
             full++;
         }
        }
        cout << "ID: "<< ids[index] << ", " << rows_array[index] <<"x"<<column_array[index]<<", empty: " << rows_array[index]*column_array[index]-full<<". Chemicals: ";
        for(int i =0; i<chemical_number;i++){
            if(chemical_cabinet_ids[i]==id){
                char location[2];
                int row = chemical_rows[i];
                int column = chemical_columns[i];
                if(row==0){
                    location[0] = 'A';
                }
                else if(row==1){
                    location[0] = 'B';
                }
                else if(row==2){
                    location[0] = 'C';
                }
                else if(row==3){
                    location[0] = 'D';
                }
                else if(row==4){
                    location[0] = 'E';
                }
                else if(row==5){
                    location[0] = 'F';
                }
                else if(row==6){
                    location[0] = 'G';
                }
                else if(row==7){
                    location[0] = 'H';
                }
                else if(row==8){
                    location[0] = 'I';
                }
                if(column==0){
                    location[1] = '1';
                }
                else if(column==1){
                    location[1] = '2';
                }
                else if(column==2){
                    location[1] = '3';
                }
                else if(column==3){
                    location[1] = '4';
                }
                else if(column==4){
                    location[1] = '5';
                }
                else if(column==5){
                    location[1] = '6';
                }
                else if(column==6){
                    location[1] = '7';
                }
                else if(column==7){
                    location[1] = '8';
                }
                else if(column==8){
                    location[1] = '9';
                }
                cout << location << ": " << chemical_ids[i] << " ";
         }
        }
        cout << endl;
        cout << " ";
        for(int k = 0; k<columns;k++){
            cout << " "<<column_names[k] ;
        }
        cout << endl;
        
        for (int j = 0; j<rows;j++){
            cout << row_names[j] << " ";
            for(int k = 0; k<columns;k++){
                c_this_turn =0;
                r_this_turn =0;
                for(int i =0; i<chemical_number;i++){

                 if(chemical_cabinet_ids[i]==id && chemical_rows[i] == j && chemical_columns[i]==k){
                     if(chemical_type[i]==1){
                         c_this_turn = 1;
                     }
                     else{
                         r_this_turn = 1;
                     }
                 }
                }
                if(c_this_turn ==1){
                    cout << "c ";
                }
                else if(r_this_turn ==1){
                    cout << "r ";
                }
                else{
                    cout << "+ ";
                }
                
            }
            cout << endl;

        }

    }
    else{
        cout << "Cabinet "<< id << " is not in the system" <<endl;
    }
}
void LabOrganizer::removeChemical(int id, int known){
    int exists = 0;
    int index=-1;
    for(int i = 0; i<chemical_number;i++){
        if (chemical_ids[i]==id){
            exists = 1;
            index = i;
            break;
        }
    }
    if (exists == 0){
        cout << "Chemical "<< id << " is not in the system" << endl;
    }
    else{
        int* deepCopy = new int[chemical_number];
        int* deepCopy2 = new int[chemical_number];
        int* deepCopy3 = new int[chemical_number];
        int* deepCopy4 = new int[chemical_number];
        int* deepCopy5 = new int[chemical_number];


        for(int i = 0; i < chemical_number; ++i){
            deepCopy[i] = chemical_ids[i];
            deepCopy2[i] = chemical_cabinet_ids[i];
            deepCopy3[i] = chemical_rows[i];
            deepCopy4[i] = chemical_columns[i];
            deepCopy5[i] = chemical_type[i];

        }
        delete [] chemical_ids;
        delete [] chemical_cabinet_ids;
        delete [] chemical_rows;
        delete [] chemical_columns;
        delete [] chemical_type;
        
        chemical_number--;
        
        
        chemical_ids = new int[ chemical_number ];
        chemical_cabinet_ids = new int[ chemical_number ];
        chemical_rows = new int[ chemical_number ];
        chemical_columns = new int[ chemical_number ];
        chemical_type = new int[ chemical_number ];

        for (int i = 0; i < index; i++) {
            chemical_ids[ i ] = deepCopy[i];
            chemical_cabinet_ids[ i ] = deepCopy2[i];
            chemical_rows[ i ] = deepCopy3[i];
            chemical_columns[ i ] = deepCopy4[i];
            chemical_type[ i ] = deepCopy5[i];

        }
        for (int i = index + 1; i < chemical_number+1; i++) {
            chemical_ids[ i -1] = deepCopy[i];
            chemical_cabinet_ids[ i -1] = deepCopy2[i];
            chemical_rows[ i -1] = deepCopy3[i];
            chemical_columns[ i -1] = deepCopy4[i];
            chemical_type[ i -1] = deepCopy5[i];

            
        }
    delete [] deepCopy;
    delete [] deepCopy2;
    delete [] deepCopy3;
    delete [] deepCopy4;
    delete [] deepCopy5;
        if(known==0){
            cout << "Chemical " << id << " removed from cabinet "<< chemical_cabinet_ids[index]<< endl;
        }

    }

}
                 
