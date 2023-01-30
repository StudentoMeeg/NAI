#include <iostream>
#include <fstream>
#include "json.hpp"

int linesNeeded (std::string text, int width) {
    int lines = 1;
    for(int i = 0; i < text.length(); i++) {
        if(i==width-4) {
            width *= 2;
            lines++;
        }
    }
    return lines;
}

int main(){
    using json = nlohmann::json;
    using namespace std;
    std::ifstream f("../data/config.json");
    json data = json::parse(f);
    cout << data << endl << endl;

    string text = data.at("text");
    int textHeight = data.at("h");
    int textWidth = data.at("w");
    int printWidth = textWidth-4;

    int emptyLines = textHeight - 2 - linesNeeded(text, textWidth);

    //1 linia ramki
    for(int i = 0 ; i < textWidth; i++) cout<<"*";

    //puste linie przed tekstem
    if(emptyLines > 0) {
        for (int i = 0; i < emptyLines/2; i++) {
            cout << "\n*";

            for (int j = 0; j < textWidth-2; j++) {
                cout << " ";
            }
            cout << "*";
        }
    }

    //wypisanie tekstu posrodku
    cout<<"\n*";

    if(text.length()%2!=0) {
        cout<<" ";
    }

    int linesIN = 1;
    for(int i = 0; i < text.length(); i++) {

        if(i==printWidth) {
            cout << " *" << endl << "* ";
            printWidth *= 2;
            linesIN++;
        }
        if(linesIN == linesNeeded(text, textWidth)) {
            for(int j = 0; j < (textWidth-(text.length()-i)-3)/2; j++) {
                cout << " ";
            }
            for(int o = i; o < text.length(); o++) {
                cout << text[o];
            }
            for(int x = 0; x < (textWidth-(text.length()-i)-3)/2; x++) {
                cout << " ";
            }
            break;
        }
        cout << text[i];
    }

    cout<<"*";

    //puste linie po tekscie
    if(emptyLines!=0) {
        if(emptyLines % 2 != 0) {
            emptyLines++;
        }
        for (int i = 0; i < emptyLines/2; i++) {
            cout << "\n*";
            for (int j = 0; j < textWidth-2; j++) {
                cout << " ";
            }
            cout << "*";
        }
    }
    cout<<"\n";

    //zamkniecie ramki
    for(int i = 0 ; i < textWidth; i++) {
        cout<<"*";
    }

    return 0;
}