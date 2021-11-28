//
//  LabOrganizer.hpp
//  homework
//
//  Created by Gün Kaynar on 7.11.2021.
//

#ifndef LabOrganizer_h
#define LabOrganizer_h

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class LabOrganizer{
public:
    LabOrganizer();
    ~LabOrganizer();
    
    void addCabinet(const int id, int rows, int columns);
    void removeCabinet(int id);
    void listCabinets();
    void cabinetContents(int id);
    void placeChemical(int cabinetId, string location, string chemType, int chemID);
    void findChemical(int id);
    void removeChemical(int id, int known=0);
    
    
    
    
private:
    int size;
    int* ids;
    int* rows_array;
    int* column_array;
    
    int chemical_number;
    int* chemical_ids;
    int* chemical_cabinet_ids;
    int* chemical_rows;
    int* chemical_columns;
    int* chemical_type;
    
    void findPlace(int cabinetId, int rows, int columns, int type,int chemID);
    int combustivePlacable(int type, int cabinetId, int row, int column);
};
#endif

