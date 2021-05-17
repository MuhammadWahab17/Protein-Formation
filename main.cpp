#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
using namespace std;
string readFastaFile(string path);
void readCsvFile(string path);
string transcribe(string dnaString);
vector<string> translate(string mrnaString);
//global vector of vectors (2Dimensional vector)list
vector<vector<string>> mycodons;
string readFastaFile(string path)
{
    string dnaString;
    fstream newfile;
    newfile.open(path,ios::in); // open a file to perform read operation usin file object
    if(newfile.is_open()){   //checking whether the file is open
        string line;
        getline(newfile, line);
        while(getline(newfile, line)){ //read data from file object and put it␣ 􏰀→into string.
            dnaString += line;
        }
        newfile.close(); //close the file object.
    }
    //cout << dnaString.substr(0,100)<< endl;
    return dnaString;
}
void readCsvFile(string path)
{
    ifstream inFile;
    string codon,Abv, AAcode, name;
    inFile.open(path);
    //read the first entry as column headers
    getline ( inFile, codon, ',' );
    getline ( inFile, Abv, ',' );
    getline ( inFile, AAcode, ',' );
    inFile >> name;
    while (!inFile.eof()) {//while we have not reached the end of file
        //read next entry
        getline ( inFile, codon, ',' );
        getline ( inFile, Abv, ',' );
        getline ( inFile, AAcode, ',' );
        inFile >> name;
        vector<string> temp;
        codon.erase(std::remove_if(codon.begin(), codon.end(), ::isspace), codon.
                    end());//clear from white space characters
        temp.push_back(codon);
        AAcode.erase(std::remove_if(AAcode.begin(), AAcode.end(), ::isspace),AAcode.end());//clear from white space characters
        temp.push_back(AAcode); // add a vector entry consisting of codon and␣ 􏰀→AAcode
        mycodons.push_back(temp);//add the vector to mycodons 2D vector
    }
}
vector<string> translate(string mrna_string)
{
    vector<string> protein;
    for (int i=0; i<mrna_string.length()-2; i++) {
    A:  string cdn = "";
        string start;
        start = mrna_string[i];
        start += mrna_string[i+1];
        start += mrna_string[i+2];
        if(start == "AUG"){
            cdn += "M";
        for (int k = i+3; k<mrna_string.length()-2; k++)
            {
                string val;
                val = mrna_string[k];
                val += mrna_string[k+1];
                val += mrna_string[k+2];
                for(int j =0; i< mycodons.size();j++){
                    if(val == mycodons[j][0])
                    {
                        cdn+=mycodons[j][1];
                        if(mycodons[j][1] == "Stop")
                        {
                            i = k;
                            protein.push_back(cdn);
                            cdn="";
                            goto A;
                        }
                        k+=3;
                        break;
                    }
                }
            }
        }
    }
    return protein;
}
string transcribe(string dna_string){
    for (int i=0; i<dna_string.length(); i++) {
        if(dna_string[i] == 'A')
            dna_string[i] = 'U';
        else if(dna_string[i] == 'T')
            dna_string[i] = 'A';
        else if(dna_string[i] == 'G')
            dna_string[i] = 'C';
        else if(dna_string[i] == 'C')
            dna_string[i] = 'G';
        else
            dna_string[i] = '\0';
    }
    return dna_string;
}
void print_protein_list(vector<string> list)
{
    for(string line : list)
    {
        cout << line << endl;
    }
    cout << list.size() << " proteins listed" << endl;
}




int main() {
    
    string dnastring = readFastaFile("ecoli.txt");
    cout<<dnastring;
//    readCsvFile("codon_table.csv");
//    string mrnastring = transcribe(dnastring);
//    vector<string> protein_list = translate(mrnastring);
//    print_protein_list(protein_list);
    return 0;
    
}

