#ifndef SMOOTHING_FILTER_HXX
#define SMOOTHING_FILTER_HXX

#include "SmoothingFilter.h"




template< typename TImage>
SmoothingFilter<TImage>::SmoothingFilter(): NbNeighbours(4)
{}



template<typename TImage>
void SmoothingFilter<TImage>::GenerateData(){


    /** Pointers intialisation */
    ImageConstPointer input = this->GetInput();
    ImagePointer output = TImage::New();
    output->Graft(this->GetInput());



    /*output->SetRegions(input->GetLargestPossibleRegion());
    output->Allocate();*/

    /** Pointers and iterators link */
    Iterator outputIterator(output, output->GetRequestedRegion());
    ConstIterator inputIterator(input, input->GetRequestedRegion());

    SizeType size = input->GetRequestedRegion().GetSize();
    TIndex limit = inputIterator.GetIndex()+size;
    /** Init mean, mean of 4 neighbours and current pixel */
    TPixel mean;



    /** For all the Image */
    while(!inputIterator.IsAtEnd())
    {

        if(IsInBundarie(inputIterator.GetIndex(), input, limit)==true)
            outputIterator.Set(input->GetPixel(inputIterator.GetIndex()));

        else{

            /** Mean - 4 Neighbours */
            if(NbNeighbours == 4)
                mean = Neighbours_4(input, inputIterator);

            /** Mean - 8 Neighbours */
            if(NbNeighbours == 8)
                mean = Neighbours_8(input, inputIterator);




            outputIterator.Set(mean);


        }

        this->GraftOutput(output);
        ++ outputIterator;
        ++ inputIterator;

    }


    return;
}





template<typename TImage>
typename TImage::PixelType SmoothingFilter<TImage>::Neighbours_4(ImageConstPointer input, ConstIterator inputIterator)
{
    TPixel mean = input->GetPixel(inputIterator.GetIndex());
    TIndex PixelIndexCurrent;
    int count =1;

    for(unsigned int i = 0; i<inputIterator.GetIndex().GetIndexDimension(); i++)
    {



        PixelIndexCurrent = inputIterator.GetIndex();

        /** PixelIndex - 1 */
        PixelIndexCurrent[i] = inputIterator.GetIndex()[i]-1;

        mean = (mean + input->GetPixel(PixelIndexCurrent));


        /** PixelIndex + 1 */
        PixelIndexCurrent[i] = inputIterator.GetIndex()[i]+1;

        mean = (mean + input->GetPixel(PixelIndexCurrent));

        count += 2;
    }
    //mean = mean/((float)(1 + 2*inputIterator.GetIndex().GetIndexDimension()));
    //std::cout<<"coutc"<<(float)count<<std::endl;
    mean = mean/(float)count;

    return mean;

}






template<typename TImage>
typename TImage::PixelType SmoothingFilter<TImage>::Neighbours_8(ImageConstPointer input, ConstIterator inputIterator)
{
    TPixel  mean=0;
    TIndex PixelIndexCurrent;
    PixelIndexCurrent = inputIterator.GetIndex();


    for(int x = -1; x <=1; x ++)
    {
        PixelIndexCurrent[0] = inputIterator.GetIndex()[0] + x;

        for(int y = -1; y <= 1; y ++)
        {
            PixelIndexCurrent[1] = inputIterator.GetIndex()[1] + y;
            if(mean == 0)
                mean = input->GetPixel(PixelIndexCurrent);
            else
                mean = (mean + input->GetPixel(PixelIndexCurrent));
        }
    }
    mean = mean/7;
    return mean;

}





template<typename TImage>
bool SmoothingFilter<TImage>::IsInBundarie(TIndex PixelIndex, ImageConstPointer input, TIndex limit)
{

    for(int i = 0; i<PixelIndex.GetIndexDimension(); i++)
    {
        if(PixelIndex[i]==0 || PixelIndex[i]== limit[i]-1)
            return true;
    }
    return false;
}






#endif
