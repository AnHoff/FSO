#include <stdio.h>
#include <stdlib.h>

int main()
{

    int qntFrames;
    int qntPageFaults = 0;
    int frames;
    int flag;

    scanf("%d",&frames);
    scanf("%d",&qntFrames);

    int incomingStream[qntFrames];

    for(int i =0; i< qntFrames; i++){
        scanf("%d", &incomingStream[i]);
    }
    int temp[frames];
    for(int i = 0; i < frames; i++)
    {
        temp[i] = -1;
    }

    for(int i = 0; i < qntFrames; i++)
    {
        flag = 0;

        for(int j = 0; j < frames; j++)
        {
            if(incomingStream[i] == temp[j])
            {
                flag++;
                qntPageFaults --;
            }
        }
        qntPageFaults ++;

         if(flag == 0)
        {
            temp[(qntPageFaults  - 1) % frames] = incomingStream[i];
        }
    }

    printf("%d\n", qntPageFaults );
    return 0;
}