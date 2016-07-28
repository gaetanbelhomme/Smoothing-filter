#ifndef SMOOTHING_FILTER_HXX
#define SMOOTHING_FILTER_HXX

#include "SmoothingFilter.h"




template< typename TImage>
SmoothingFilter<TImage>::SmoothingFilter(): NbNeighbours(4)
{}


/** Process the smooth filter **/
template<typename TImage>
void SmoothingFilter<TImage>::GenerateData(){


    /** Pointers intialisation */
    ImageConstPointer input = this->GetInput();
    ImagePointer output = TImage::New();
    output->Graft(this->GetInput());


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
            {
                mean = Neighbours_8(input, inputIterator);
            }

            outputIterator.Set(mean);


        }

        this->GraftOutput(output);
        ++ outputIterator;
        ++ inputIterator;

    }


    return;
}




/** Mean for 4 neighbours **/
template<typename TImage>
typename TImage::PixelType SmoothingFilter<TImage>::Neighbours_4(ImageConstPointer input, ConstIterator inputIterator)
{
    itk::RGBPixel<float> mean = input->GetPixel(inputIterator.GetIndex());
    if(TImage::GetImageDimension()==2)
        itk::RGBPixel<int> mean = input->GetPixel(inputIterator.GetIndex());


    TIndex PixelIndexCurrent;
    int count =1;

    for(unsigned int i = 0; i<inputIterator.GetIndex().GetIndexDimension(); i++)
    {
        for(unsigned int j = 0; j<3; j++)
        {

            PixelIndexCurrent = inputIterator.GetIndex();

            /** PixelIndex - 1 */
            PixelIndexCurrent[i] = inputIterator.GetIndex()[i]-1;

            mean[j] = (mean[j] + input->GetPixel(PixelIndexCurrent)[j]);


            /** PixelIndex + 1 */
            PixelIndexCurrent[i] = inputIterator.GetIndex()[i]+1;

            mean[j] = (mean[j] + input->GetPixel(PixelIndexCurrent)[j]);
        }

        count += 2;
    }
    for(unsigned k = 0; k<3; k++)
        mean[k] = mean[k]/(float)count;

    return mean;

}



/** Mean for 8 neighbours **/
template<typename TImage>
typename TImage::PixelType SmoothingFilter<TImage>::Neighbours_8(ImageConstPointer input, ConstIterator inputIterator)
{
    itk::RGBPixel<int>  mean;
    mean[0] = 0,mean[1] = 0, mean[2] = 0;
    TIndex PixelIndexCurrent;
    PixelIndexCurrent = inputIterator.GetIndex();


    for(int x = -1; x <=1; x ++)
    {
        PixelIndexCurrent[0] = inputIterator.GetIndex()[0] + x;

        for(int y = -1; y <= 1; y ++)
        {
            PixelIndexCurrent[1] = inputIterator.GetIndex()[1] + y;
            if(mean[0] == 0 && mean[1] == 0 && mean[3] == 0)
                mean = input->GetPixel(PixelIndexCurrent);
            else
            {
                for(unsigned int j = 0; j<3; j++)
                    mean[j] = (mean[j] + input->GetPixel(PixelIndexCurrent)[j]);
            }

        }
    }
    mean[0] = mean[0]/7;
    mean[1] = mean[1]/7;
    mean[2] = mean[2]/7;
    return mean;

}



/** If the current pixel is on bundaries (index = 0 or index = image.size-1), we set it at imageinput value **/
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
