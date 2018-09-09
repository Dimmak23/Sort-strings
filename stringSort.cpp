#include <iostream>
#include <cstring>
#include <string>

class Sorted

{
    
    //Size and contains of original, sorted arrays a kept private.
    private:
        // Declaring (int)lines - container of lines quantity
        // and (string)input - container of original sentence,
        // (int)size would be size of this sentence.
        int lines=0, size=0; std::string input;
        // Declaring (int)pure - container of quantity items
        // in the sorted array after removing all 'space' signs
        // (char)*bubble - pointer for this array.
        int pure=0; char *bubble = new char[100];
        // Declaring of the array (int)repeat[100] with maximum
        // 100-places for items from sorted array,
        // (int)MAX - container of maximum times all letters repeats,
        // (int)qty - container of quantity unique most repeated letters.
        // (string)letters - container of most repeated letters.
        int repeat[100]={0}, MAX=0, qty=0;
        std::string letters;
        // (int)MIN - container of minimum times all letters repeats,
        // (int)uni - container of quantity unique less repeated letters.
        // (string)unilet - container of less repeated letters.
        int MIN=0, uni=0;
        std::string unilet;
        // (int)false_space - container for keeping false spaces count.
        int false_space = 0;
        
    //In the main program accessible next methods:
    public:
        // Temporary string container
        std::string tempo;

        //Ask user about oirignal array
        char setData()
        {
            // You enter quantity of lines here
            std::cout<<"\nEnter quantity of lines: ";
            std::cin>>lines;

            // Sentence for research line-by-line you enter here
            std::cout<<"\nEnter sentences:\n\n";      
            
            // Every new line will be stored by adding 'space' sign,
            // without adding 'space' sign we no longer can classify
            // every new line after. Other 'spaces' will be saved.
            for(int i = 0; i <= lines; ++i)
                {
                    std::getline(std::cin, tempo);
                    if (i > 1){
                        input += ' ';
                        false_space++;
                    }
                    input += tempo;
                }
            // Seting size of orginal sentence
            size = input.size();
        }

        // Method for getting original input sentence
        char getData(int i) { return input[i]; }

        // Method for getting quantity of repeats of sorted items
        int getRepeat(int i) { return repeat[i]; }

        // Method that copy data from store with removing spaces
        void copyPurePast()
        {
            // Temporary used variable counter of *bubble items array
            int j=0;
            for(int i = 0; i < size;++i)
                {
                    // Clear signs that not a letters
                    if ( ( (int)(getData(i)) < 32 ) ) continue;
                    // In the ANSI c/c++ table for sign 'space'
                    // correspond integer code 32.
                    // If find (int)32 than you find 'space',
                    // delete false spaces.
                    if ( ( (int)(getData(i)) == 32 ) && (false_space-- > 0) ) continue;
                    *(bubble + j++)=getData(i);
                }
            // Seting size of "pure" entered array
            pure=j;
        }
        
        // Method wich calculate every time when item from sorted array
        // appear in this array. For items finds only once there
        // would be repeat[i]=1, etc.
        void setRepeat()
        {
            for(int i=0;i<pure;++i)
                for(int j=0;j<pure;++j)
                    // It's simple: find equal letter add 1.
                    if( (int)(*(bubble+j)) == (int)(*(bubble+i)) ) ++repeat[i];
        }

        //Apply method for bubble sorting
        void sortDataBubble()
        {   
            // Before sorting array let's remove any 'space' signs from it
            copyPurePast();
            
            // Temporary used variables for item and size of researched arrays
            char temp=0; int N=pure;
            
            // Simple bubble algorithm for data sorting in the array
            while(--N>0)
                {
                    for(int i=1;i<=N;++i)
                        // Every item with bigger integer ANSI code will
                        // flow to the up in the array like bubble.
                        if( (int)(*(bubble+i-1)) > (int)(*(bubble+i)) )
                            {
                                temp=*(bubble+i);
                                *(bubble+i)=*(bubble+i-1);
                                *(bubble+i-1)=temp;
                            }
                }
        }

        // Method that find unique repeated letters and calculate
        // each time when they repeated.
        void calcRepeat()
        {
            // Calling member funcion for calculation of repeats for each letter
            // in the sorted array
            setRepeat();
            
            // Searching for maximum repeatings in the sorted array
            // ammount of repeats not get straight, but from member function
            for(int i=0;i<pure;++i) if(getRepeat(i)>MAX) MAX=getRepeat(i);

            // At first minimum set to size MAX
            MIN=MAX;
            
            // Searching for minimum repeatings in the sorted array
            // ammount of repeats not get straight, but from member function
            for(int i=0;i<pure;++i) if(getRepeat(i)<MIN) MIN=getRepeat(i);

            // Searching for all letters that repeats the most,
            // if there would be any. Cicle consider that in the
            // sorted array can be only one letter that
            // repeats all the time, or can be multiple letters
            // thats repeats equal times each.
            for(int i=0;i<pure; )
            {
                // We whant to be shure if this letter is the most repeated
                if(getRepeat(i)==MAX)
                {
                    // Let's calculate each time when we store
                    // any most repeated letter
                    ++qty;
                    tempo=*(bubble+i);
                    // For output word also provided
                    // guards '' - for not mistake founded
                    // letters with printed text.
                    letters+=" '"+tempo+"',";
                }
                
                // We whant to be shure if this letter is the less repeated 
                if(getRepeat(i)==MIN)
                {
                    // Let's calculate each time when we store
                    // any less repeated letter
                    ++uni;
                    tempo=*(bubble+i);
                    // For output word also provided
                    // guards '' - for not mistake founded
                    // letters with printed text.
                    unilet+=" '"+tempo+"',";
                }

                // Input array is sorted now in the *(bubble)
                // so if increase step 'i' by repeat[i] it will get us
                // to the next not researched yet number
                i+=getRepeat(i);
            }
        }      

        // Method get values of MAX, MIN, qty and uni for main()
        void getPoints(int &a, int &b, int &c, int &d)
        {
            a=MAX; b=MIN; c=qty; d=uni;
        }

        // Print stored or sorted data
        void printData(int x)
        {
            // For entered '1' printed original sentence.
            if(x==1)
                {
                    std::cout<<"\nProgram stored data:\n"; 
                    std::cout<<input;
                }
            // For entered '2' printed sorted data.
            if(x==2)
                {
                    std::cout<<"\nBubble sorted data:\n";
                    for(int i=0;i<pure;++i) std::cout<<(char)(*(bubble+i));
                }
            // Every output provides with end flag. With end flag we shure where
            // result is ends. If entered sentence got 'spaces' in the end
            // they will be printed.
            std::cout<<"<-end flag\n";
        }

        // Print result of search for repeatings
        void printRepeat(int M, int Q, int &x)
        {
            // Mode '1' printed MOST repeated.
            // Mode '2' printed LESS repeated.
            // Here printed result for sentences with only one letter that
            // multiple times or multiple letters, which repeats equal times.
            // By operator && x and further --x; we shure that if we already
            // print this result - we do not print it in the future.
            if( ((Q*M)==pure) && x )
                {
                    std::cout<<"\nResult of research for the repeated letters.";
                    // Only one letter.
                    if(Q==1)
                        {
                            std::cout<<"\nEntered sentence contains "
                                    <<"only one letter"<<letters
                                    <<" that repeated "<<M<<" times.\n";
                        }
                    // Multiple letters.
                    if(Q>1)
                        {
                            std::cout<<"\nEntered sentence did not contain"
                                    <<" any most or less repeated letters."
                                    <<"\nAll letters repeated "<<M<<" times each.\n";
                        } 
                --x; // We no longer can print this result
                }
            
            // Here printed result for sentences with only one or multiple
            // letters which multiple times, but other letters repeated less.
            if( (Q*M)<pure && x)
                {
                    if(x==1)
                    std::cout<<"\nResult of research for the MOST repeated letters.";
                    if(x==2)
                    std::cout<<"\nResult of research for the LESS repeated letters.";                    
                    // Only one letter.
                    if(Q==1)
                        {
                            std::cout<<"\nEntered sentence contain letter";
                            if(x==1)std::cout<<letters;
                            if(x==2)std::cout<<unilet;
                            std::cout<<"\nthat repeated "<<M<<" times.\n";
                        }
                    // Multiple letters.
                    if(Q>1)                
                        {
                            std::cout<<"\nEntered sentence contain letters\n";
                            if(x==1)std::cout<<letters;
                            if(x==2)std::cout<<unilet;                            
                            std::cout<<"\nthat's repeated "<<M<<" times each.\n";
                        }
                ++x; // We can print reslt for less numbers in the future
                }
        }

};

int main()

{
    // Class for sorting strings constructed
    Sorted call;
    
    // Some main() variables, which will be helpfull next 
    int MAX = 0, MIN = 0, qty = 0, uni = 0;
    
    // Ask user for initial sentence  
    call.setData(); 
    
    // Actual sorting
    call.sortDataBubble();
    
    // Looking for repeatings
    call.calcRepeat();
    
    // Asking for result to manipulate with method printRepeat() next
    call.getPoints(MAX,MIN,qty,uni);
    
    // Print initial input  
    call.printData(1);
    
    // Print sorted string     
    call.printData(2);
    
    // Set initial printing mode for MOST repeated letters
    int x = 1;
    call.printRepeat(MAX,qty,x);
    
    // If printRepeat() allow we will get result for LESS repeated letters
    call.printRepeat(MIN,uni,x);

    return 0;
}
