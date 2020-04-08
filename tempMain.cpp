#include <iostream>
#include <fstream>
#include <string>

const static int NUMBER = 0;
const static int MGI_SYMBOL = 1;
const static int HGNC_SYMBOL = 2;
const static int CHROMOSOME = 3;
const static int GENE = 4;
const static int ROWSIZE= 4;
const static int GENE_COLUMN_SIZE= 5;
const static int GENE_ROW_SIZE= 14340;



using namespace std;
int main() {
    string geneArray[GENE_COLUMN_SIZE];
    string str_male_healthy;
    string str_gene;
    int counter = 1;


    ifstream ifile_gene("../Dataset/geneAnnotation.csv");
    if(ifile_gene.fail()){
        cerr << "Failed to open file." << endl;
        return -1;
    }

    ifstream ifile_Male_healthy("../Dataset/Male_healthy.csv");
    if(ifile_Male_healthy.fail()){
        cerr << "Failed to open file." << endl;
        return -1;
    }
    ifile_Male_healthy.close();

    //read header
    getline(ifile_gene, str_gene);
    getline(ifile_Male_healthy, str_male_healthy);

    for(int n = 0; n < GENE_ROW_SIZE; n++){
        ifile_Male_healthy.open("../Dataset/Male_healthy.csv");
        for(int i = 0; i < CHROMOSOME; i++)
            getline(ifile_gene, geneArray[i], ',');

        getline(ifile_Male_healthy, str_male_healthy, ',');

        cout << geneArray[MGI_SYMBOL] << ' ' << str_male_healthy << endl;

        while(geneArray[MGI_SYMBOL] != str_male_healthy){
            ifile_Male_healthy.ignore(100000, '\n');
            getline(ifile_Male_healthy, str_male_healthy, ',');
            counter++;

            cout << "\r" << "Progress: " << counter << " / " << GENE_ROW_SIZE << string(10, ' ');
            fflush(stdout);
        }

        cout << counter << "Found it!" << endl;
        counter = 1;

        //cout << geneArray[MGI_SYMBOL] << ' ' << geneArray[HGNC_SYMBOL] << endl;
        //getline(ifile_Male_healthy, str_male_healthy);
        //getline(ifile_Male_healthy, str_male_healthy);
        ifile_Male_healthy.ignore(100000, '\n');
        getline(ifile_gene, str_gene);

        ifile_Male_healthy.close();
    }


    return 0;
}
