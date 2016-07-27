#include "SmoothingFilter.hxx"



#include "itkImage.h"
#include "itkImageToImageFilter.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "QuickView.h"



int main( int argc, char * argv[])
{
    if ( argc < 2)
    {
        std::cerr << "Usage: " << std::endl;
        std::cerr << argv[0] << "  inputImageFile " << std::endl;
        return EXIT_FAILURE;
    }



    /** Get Dimension & extension */
    //Dimension
    int dim = 0;

    do{
        std::cout<< "Dimension ? "<<std::endl;
        std::cin>>dim;

    }while(dim >3 || dim <2);


    //Extension
    std::string exten;
    std::cout<<"extension ?"<<std::endl;
    std::cin>>exten;




    /** Image type */
    //typedef itk::RGBPixel<float> PixelType;
    typedef unsigned char PixelType;
    //typedef itk::VariableLengthVector<float> PixelType;

    if(dim == 2)
    {
        const unsigned int Dimension = 2;

        typedef itk::Image<PixelType, Dimension>        ImageType;
        typedef itk::ImageFileReader<ImageType>         ReaderType;
        typedef itk::ImageFileWriter<ImageType>         WriterType;
        typedef SmoothingFilter<ImageType>              FilterType;

        ReaderType::Pointer reader = ReaderType::New();
        WriterType::Pointer writer = WriterType::New();
        FilterType::Pointer filter = FilterType::New();



        /** Set Neighbourhood */
        do{
            std::cout<< "Neighbours :"<<std::endl;
            std::cin>>filter->NbNeighbours;
        }while(filter->NbNeighbours!=4 && filter->NbNeighbours!=8);

        /** Read    */
        reader->SetFileName(argv[1]+exten);
        reader->Update();

        /** Filter  */
        filter->SetInput(reader->GetOutput());
        filter->Update();

        /** Writer  */
        std::string name = "_out";
        writer->SetInput(filter->GetOutput());
        writer->SetFileName(argv[1] + name + exten);
        writer->Update();

//        QuickView viewer;
//        viewer.AddImage(reader->GetOutput(), true, "Original Image");
//        viewer.AddImage(filter->GetOutput(), true, "Filtered Image");
//        viewer.Visualize();
    }



    else
    {
        const unsigned int Dimension = 3;

        typedef itk::Image<PixelType, Dimension>        ImageType;
        typedef itk::ImageFileReader<ImageType>         ReaderType;
        typedef itk::ImageFileWriter<ImageType>         WriterType;
        typedef SmoothingFilter<ImageType>              FilterType;

        ReaderType::Pointer reader = ReaderType::New();
        WriterType::Pointer writer = WriterType::New();
        FilterType::Pointer filter = FilterType::New();

        /** Read    */
        reader->SetFileName(argv[1]+exten);
        reader->Update();

        /** Filter  */
        filter->SetInput(reader->GetOutput());
        filter->Update();

        /** Writer  */
        std::string name = "_out";
        writer->SetInput(filter->GetOutput());
        writer->SetFileName(argv[1] + name + exten);
        writer->Update();
    }



    return 0;

}
