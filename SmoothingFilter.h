#ifndef SMOOTHING_FILTER_H
#define SMOOTHING_FILTER_H

#include "itkImage.h"
#include "itkImageToImageFilter.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"


template< typename TImage>
class SmoothingFilter: public itk::ImageToImageFilter< TImage, TImage >
{

public:

    /** Standard class typedefs. */
    typedef SmoothingFilter                                 Self;
    typedef itk::ImageToImageFilter< TImage, TImage >       SuperClass;
    typedef itk::SmartPointer<Self>                         Pointer;
    typedef itk::SmartPointer<const Self>                   ConstPointer;
    typedef itk::ImageRegionIterator<TImage>                Iterator;
    typedef itk::ImageRegionConstIterator<TImage>           ConstIterator;

    typedef typename TImage::PixelType                      TPixel;
    typedef typename TImage::IndexType                      TIndex;
    typedef typename TImage::ConstPointer                   ImageConstPointer;
    typedef typename TImage::Pointer                        ImagePointer;
    typedef typename TImage::SizeType                       SizeType;


    /** Method for creation through the object factory  */
    itkNewMacro(Self)

    /** Run-time type information (and related methods) */
    itkTypeMacro(SmoothingFilter, ImageToImageFilter)

    /** Number of Neighbours */
    int NbNeighbours;



protected:

    SmoothingFilter();

    /** Does the real work */
    virtual void GenerateData();

private:

    bool IsInBundarie(TIndex PixelIndex, ImageConstPointer input, TIndex limit);

    TPixel Neighbours_4(ImageConstPointer input, ConstIterator inputIterator);
    TPixel Neighbours_8(ImageConstPointer input, ConstIterator inputIterator);


};




#endif
