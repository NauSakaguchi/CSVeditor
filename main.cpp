#include <iostream>
#include <fstream>
#include <string>

const static int NUMBER = 0;
const static int MGI_SYMBOL = 1;
const static int HGNC_SYMBOL = 2;
const static int CHROMOSOME = 3;
const static int GENE = 4;
const static int ROWSIZE= 4;
const static int GENE_COLUMN_SIZE= 3;
const static int GENE_ROW_SIZE= 14003;
const static int MALE_ROW_SIZE= 16273;
//const static int MALE_ROW_SIZE= 20;

using namespace std;

string upperCase(string name){
    for (int i=0;i< name.size();i++)
        //入力された文字列を大文字に変換
        name[i]=toupper(name[i]);
    return name;
}

bool samestring(string name1, string name2){
    //upperCase関数で変換した後、等価判定
    if(upperCase(name1) == upperCase(name2))
        return true;
    else
        return false;
}

int main() {
    string geneArray[GENE_COLUMN_SIZE];
    string str_male_healthy;
    string str_gene;
    int counter = 0;
    int find_counter = 0;
    int not_find_counter = 0;
    int checkarray[200] = {0};


    ifstream ifile_gene("../Dataset/geneAnnotation2.csv");
    if(ifile_gene.fail()){
        cerr << "Failed to open file." << endl;
        return -1;
    }

    ifstream ifile_Male_healthy("../Dataset/Male_healthy.csv");
    if(ifile_Male_healthy.fail()){
        cerr << "Failed to open file." << endl;
        return -1;
    }

    ofstream outputfile("../Dataset/test.csv");

    //read header
    getline(ifile_Male_healthy, str_male_healthy);
    outputfile << str_male_healthy;

    outputfile << endl;

    ifile_gene.close();

    for(int n = 0; n < MALE_ROW_SIZE; n++){
        ifile_gene.open("../Dataset/geneAnnotation2.csv");
        getline(ifile_gene, str_gene);

        for(int i = 0; i < HGNC_SYMBOL; i++)
            getline(ifile_gene, geneArray[i], ',');
        getline(ifile_gene, geneArray[HGNC_SYMBOL]);

        getline(ifile_Male_healthy, str_male_healthy, ',');

        cout << str_male_healthy << ":" << endl;

        //while(geneArray[MGI_SYMBOL] != str_male_healthy && counter <= GENE_ROW_SIZE){
        while(!samestring(geneArray[MGI_SYMBOL], str_male_healthy) && counter <= GENE_ROW_SIZE){
            ifile_gene.ignore(1000, '\n');
            for(int i = 0; i < HGNC_SYMBOL; i++)
                getline(ifile_gene, geneArray[i], ',');
            counter++;

            //cout << "\r" << "Progress: " << counter << " / " << GENE_ROW_SIZE << string(10, ' ');
            //fflush(stdout);
        }

        if(counter > GENE_ROW_SIZE){
            cout << "Not Found" << endl;
            not_find_counter++;
            ifile_Male_healthy.ignore(100000000000, '\n');
        }
        else{
            cout << "Found it! : " << counter << endl;

            getline(ifile_gene, geneArray[HGNC_SYMBOL]);
            outputfile << geneArray[HGNC_SYMBOL] << ",";


            getline(ifile_Male_healthy, str_male_healthy);
            outputfile << str_male_healthy << endl;

            checkarray[counter/100]++;
            find_counter++;
        }
        counter = 0;

        //cout << geneArray[MGI_SYMBOL] << ' ' << geneArray[HGNC_SYMBOL] << endl;
        //getline(ifile_Male_healthy, str_male_healthy);
        //getline(ifile_Male_healthy, str_male_healthy);


        ifile_gene.close();
    }

    outputfile.close();

    /**
    for(int i = 0; i < 200; i++){
        cout << i << "01 - " << i + 1 <<"00 " << checkarray[i] << endl;
    }
    **/
    cout << "Total(not find): " << not_find_counter << endl;
    cout << "Total: " << find_counter;
    return 0;
}
