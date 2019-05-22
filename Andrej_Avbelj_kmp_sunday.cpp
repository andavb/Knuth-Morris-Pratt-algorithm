#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

string preberiDatoteko(string ime){
	std::ifstream inFile;
    inFile.open(ime);
    
    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string str = strStream.str();

    return str;
}

int* calculateKMPnext(string isk, int dolzina){

	int* KMPnext = new int[dolzina];
	int pomoc = 0, stevec = 2;


	KMPnext[0] = -1;
	KMPnext[1] = 0;

	while(stevec < dolzina){

		if(isk[stevec-1]==isk[pomoc]){
			KMPnext[stevec] = pomoc+1;
			pomoc++;
			stevec++;
		}
		else if(pomoc > 0){
			pomoc = KMPnext[pomoc];
		}
		else{
			KMPnext[stevec] = 0;
			stevec++;
		}
	}

	return KMPnext;
}

std::vector<int> KMPalgoritem(string iskani, string besedilo){

	std::vector<int> ujemanja;

	int besediloSt = besedilo.length(), iskaniSt = iskani.length(), i = 0, b = 0;

	int *polje = calculateKMPnext(iskani, iskaniSt);


	while((i+b) < besediloSt){

		if(iskani[i] == besedilo[b+i]){

			if(i == (iskaniSt-1)){
				ujemanja.push_back(b);
			}
			i++;
		}
		else{
			if(polje[i] > -1 && i < iskaniSt){

				b = b + i - polje[i];
				i = polje[i];
			}
			else{
				b++;
				i = 0;
			}
		}
	}

	for (int i = 0; i < ujemanja.size(); ++i)
	{
		cout << ujemanja[i] << endl;
	}

	delete(polje);
	return ujemanja;
}

int*  BCHgeneriraj(string x, int m, string y, int b){

	int* BCHpolje = new int[127];

	for (int i = 0; i < 127; i++)
	{
		BCHpolje[i]=-1;
	}

	for (int i = 0; i < m; i++)
	{
		BCHpolje[x[i]]=m-i;
	}

	for (int i = 0; i < b; i++)
	{
		if(BCHpolje[y[i]] < 0){
			BCHpolje[y[i]]=m+1;
		}
	}

	/*for (int i = 0; i < 127; ++i)
	{
		cout << BCHpolje[i] << " " << i << endl;
	}*/

   return BCHpolje;

}

std::vector<int> SundaySearchAlg(string iskani, string besedilo){

	std::vector<int> ujemanja;

	int besediloSt = besedilo.length(), iskaniSt = iskani.length(), i = 0, b = 0;

	int *BCH = BCHgeneriraj(iskani, iskaniSt, besedilo, besediloSt);
	int s = 0;

	while(s < (besediloSt-iskaniSt)){
		int j = 0;

		while (j < iskaniSt && iskani[j] == besedilo[s + j]){
			//cout << "iskan " << iskani[j] << " besedilo: " << besedilo[s + j] << endl;
			j++;
		}

		if(j == iskaniSt){
			ujemanja.push_back(s);
			s += iskaniSt;
		}
		else{
			//cout << " BCH[besedilo[j+iskaniSt]] " << BCH[besedilo[s+iskaniSt]] << " nix " << s+iskaniSt << " crka: " << besedilo[s+iskaniSt]<< endl;
			s += BCH[besedilo[s+iskaniSt]];
			//cout << " s = " << s << endl;
		}
	}

	return ujemanja;
}

int main(int argc, char** argv)
{	
	char  *file;
	string  iskalniNiz;
	std::vector<int> indexi;

	iskalniNiz = argv[2];
	file = argv[3];

	string str = preberiDatoteko(file);

	if(strcmp(argv[1],"0") == 0){
      indexi = KMPalgoritem(iskalniNiz, str);
    }
    else if (strcmp(argv[1],"1") == 0) {
      indexi = SundaySearchAlg(iskalniNiz, str);
    }
    else{
      std::cout << "Niste podali pravilnih argumentov !" << '\n';
      return 0;
    }

    std::ofstream outFile("out.txt");
    for (const auto &e : indexi){
      outFile << e << " ";
    }

	/*for(int i=0; i<indexi.size(); ++i){
  		std::cout << indexi[i] << ' ';
	}
	cout << endl;*/

    return 0;
}
