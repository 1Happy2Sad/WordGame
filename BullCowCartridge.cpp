// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include"HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(HWords); //Getting validWords from ValidWord func.
    Scores = 0;
    SetupGame(); //Setiing up the game

    
    //Reference Examples
    // int32 a = 0;
    // int32& Dene = a;
    // int32 b = 3;
    // a = b; // or Dene = b will get the same result. Because a and Dene countain same address.
    // Dene = b;
    // //Dene = &b; //Error as well
    // //&b = Dene; // Error
    // PrintLine(TEXT("%i"), Dene);
    // PrintLine(TEXT("%i"), &Dene);
    // PrintLine(TEXT("%i"), a);
    // PrintLine(TEXT("%i"), &a);
    // PrintLine(TEXT("%i"), &b);
    
    //PrintLine(TEXT("Hidden word is : %s"), *HiddenWord); //Debug Line
    
    //Pre vs Post Increment/Decrement
    // PrintLine(TEXT("a: %i"), a);
    // int32 a = 1;
    // int32 b = a++;
    // PrintLine(TEXT("a: %i, b: %i"), a, b);
    // a = 1, b = 0; //sıfırlama işlemi.
    // b = ++a;
    // PrintLine(TEXT("a: %i, b: %i"), a, b);
 
 }

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    //ClearScreen();//Clears the terminal

    if (bGameOver){ // If the game finished
            ClearScreen();
            SetupGame();//Setting up the game
        }
        else{ //If the player guess is not correct
            ProcessGuess(PlayerInput);
        }

    //Process of player guess
    
   
//Testing other if else process that not need to but they may be a good examples
    /*  if (Lives > 0){
    if (Input == HiddenWord){
        PrintLine(TEXT("Kazandin"));
    }
    else{
        if(Input.Len() != HiddenWord.Len()){
            PrintLine(TEXT("Sihirli kelime %i harf uzunlugunda"), HiddenWord.Len());
        }
        -- Lives;
        PrintLine(TEXT("%i canin kaldi"), Lives);
    }
    }
    else{
        PrintLine(TEXT("GameOver")); 
    } */
    //-------------------------------------------------------------------------------------------------------   
    /* if (Lives > 0){
        if (Input == HiddenWord){
            PrintLine(TEXT("Senin anan yani, bildin."));
        }
        else{
            PrintLine(TEXT("Burasi fight clüp, bilemdin"));
            --Lives;
            PrintLine(TEXT("Canin Kaldi")); // Can gelicek. 
        }
        }
    else{    
    PrintLine(TEXT("Canin Kalmadi. KAYBETTİN."));
    } */
}

void UBullCowCartridge::SetupGame(){

    //---------------------------------------
    //Setting function and varibles that needed
    //Setting up the Hidden words
    int32 GenRandomNum = FMath::RandRange(0,Isograms.Num() - 1);
    HiddenWord = Isograms[GenRandomNum];
    
    //Lives that player has at the start
    Lives = HiddenWord.Len()*2;
    bGameOver = false;
    
    //Save the score here.
    
    //------------------------------------------

    //------------------------------------------------------------------------------------------------------------------------------------------
    //Text area to show to player some stuff
    //Welcoming the game
    PrintLine(TEXT("Oyuna hoşgeldin!")); // with TEXT() you can type in more characters. Like ü for example.
    //Showing what they got(Lives and the lenght of the hiddenword to guess)
    PrintLine(TEXT("Canin: %i"), Lives);
    PrintLine(TEXT("\nDevam etmek için %i karakter uzulugundaki\nsihirli ismi gir..."), HiddenWord.Len());
    
    //---------------------------------------------------------------------------------------------------------------------------------------
    //Debugline
    //PrintLine(TEXT("%i adet sihirli kelime bulunmaktadir."), HWords.Num());//.Num() dizinin içerisinde kaç adet element olduğunu gösteriyor.
    //PrintLine(TEXT("%i adet geçerli sihirli kelime bulunmaktadir"), GetValidWords(HWords).Num());
    //---------------------------------------------------------------------------------------------------------------------------------------
    

    //Testing of func. and array
    // TArray<FString> Deneme;
    // ValidWords = GetValidWords(HWords);
    //PrintLine(TEXT("%i adet geçerli sihirli kelime bulunmaktadir"), ValidWords.Num());
  
    //Testing char
    //const char HW[] = "dasdsa";
    //const TCHAR HW[] = TEXT("dasd");//Without TEXT() it will be crash.
    //const TCHAR HW[] = {TEXT('c'), TEXT('a'), TEXT('k'), TEXT('e'), TEXT('s'), TEXT('\0')};
    //PrintLine(TEXT("%c"), HW[1]); 
    
    //----------------------------------------------------------------------------
    //Random number example
    //Generate random number for Hidden wordlist
    //int32 GenRandomNum = FMath::RandRange(0,GetValidWords(HWords).Num()-1);
    //int32 MaxNumArray = GetValidWords(HWords).Num()-1;
    //int32 GenRandomNum = FMath::RandRange(0,MaxNumArray);
    //HiddenWord = GetValidWords(HWords)[GenRandomNum];
    //----------------------------------------------------------------------------
}

void UBullCowCartridge::EndGame(){// If the player win the game or lose the game this func. will pop up
    bGameOver = true;
    PrintLine(TEXT("Toplam Score sayin: %i"), Scores);
    PrintLine(TEXT("\nTekrar oynamak için enter'a bas..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess){
    if (Guess == HiddenWord){// If the player guess is correct
        PrintLine(TEXT("Kazandin"));
        Scores++;
        EndGame();
        return;
    }
    
    if(Guess.Len() != HiddenWord.Len()){// if is the Pleyer input  lenght not equal to hiddenword
        //PrintLine(TEXT("Canin: %i"), Lives);
        PrintLine(TEXT("Sihirli kelime %i karakter uzunlugunda."), HiddenWord.Len());
        return;
    }
    
    if(!IsIsogram(Guess)){// Testing the player input that is the input reapeting itself as char by char. Not word by word.
        PrintLine("Ayni karakterler arka arkaya\ntekrarlanamaz!");
        return;
    }
    
    //Remove Livesw
    PrintLine(TEXT("\nCanini Yedim!"));
    --Lives;
    
    if(Lives <= 0){// If player out of lives
        ClearScreen();
        PrintLine(TEXT("Canin bitti."));
        PrintLine(TEXT("Bilemedigin sihirli kelime: %s"), *HiddenWord);
        EndGame();
        return;
    } 

    FBullCowCount Clue = GetBullCows(Guess);
    PrintLine(TEXT("Bulls : %i, Cows : %i"), Clue.Bulls, Clue.Cows);

    PrintLine(TEXT("Canin: %i"), Lives);     
    
    //Testing someting that I don't know exactly.
    // if (Guess.Len() != HiddenWord.Len() && Lives > 1){
    //     PrintLine(TEXT("Canini yerim!"));
    //     PrintLine(TEXT("Canin: %i"), --Lives);
    //     PrintLine(TEXT("Sihirli kelime %i karakter uzunlugunda"), HiddenWord.Len());
    //     return;
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const{//Checking the Isogram of thr player input
    for(int32 Index = 0; Index < Word.Len(); Index++){
        for(int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++){
            if(Word[Index] == Word[Comparison]){
                return false;
            }          
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const{//Checking the wordlist.h file for the words are valid for the game.
    TArray<FString> RightLengthWords;
    
    //Range based for loop.| for(type TempVar : Data)
    for(FString Word: WordList){//Looking trough the words
        int32 CheckLen = Word.Len();
        
        if(CheckLen >=4 && CheckLen <= 8){//Checking every word Lenght one by one
            if(IsIsogram(Word)){// Is words maintain isogram then there are not valid for the game
                RightLengthWords.Emplace(Word);
            }
          //PrintLine(TEXT("%s"), *HWords[i]);
        }
    }
    return RightLengthWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) {
    FBullCowCount Count;

    for (int32 i = 0; i < Guess.Len(); i++)
    {
        if (Guess[i] == HiddenWord[i]){// If the guess letter its in the same place with Hiddenword we will get Bull.
            Count.Bulls++;
             PrintLine(TEXT("Bulls : %c"), Guess[i]);
            continue;
        }
        for (int32 k = 0; k < HiddenWord.Len(); k++){// If the letter is same but in the different order with HiddenWord we will get Cow.
            if (Guess[i] == HiddenWord[k]){
                Count.Cows++;
                PrintLine(TEXT("Cows : %c"), Guess[i]);
                break;
            }
        }
    }
    return Count;
}


//Menu denemesi(Başarısız oldum)
// void UBullCowCartridge::GameMenu(FString MenuInput){
//     PrintLine(TEXT("1.Basla"));
//     PrintLine(TEXT("2.Toplam puan"));
//     PrintLine(TEXT("0.Cikis"));
//     // PrintLine(TEXT(": "));
//     bool bMenu = true;
//     while (bMenu){
//         GameMenuInputs(bMenu, MenuInput);
//     }
// }
// bool UBullCowCartridge::GameMenuInputs(bool& bMenu, char MenuInput){
//     switch (MenuInput)
//     {
//     case '1':
//         ClearScreen();
//         bMenu = false;
//         if (bGameOver){ // If the game finished
//             ClearScreen();
//             SetupGame();//Setting up the game
//         }
//         else{ //If the player guess is not correct
//             ProcessGuess(PlayerInput);
//         }
//     break;
//     case '2':
//         ClearScreen();
//         PrintLine(TEXT("Toplam puan: %i"), Scores);
//     break;
//     case '0':
//         ClearScreen();
//         bMenu = false;
//         return 0;
//     break; 
//     default:
//         ClearScreen();
//         PrintLine(TEXT("This is an ERROR"));
//         break;
//     }
// }


// Oyunu daha da kolaylaştırabilirsin.(İleri seviye işlem)
    // - NotePad ekleyebilirsin. (Araştırma yaspman gerekecek)
    // - Daha başka fikirle de bulabilirsin (Belki adam asmaca gibi bir sistem olabiilr.)