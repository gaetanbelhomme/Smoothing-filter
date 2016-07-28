#include "SmoothingFilter.hxx"

#include "itkImage.h"
#include "itkImageToImageFilter.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "QuickView.h"
#include "itkRGBPixel.h"



/** Find extension */
std::string SetExten(std::string file)
{
    int pos = file.find('.',2);
    std::string filename = file.substr(0,pos);
    std::string exten = file.substr(pos,file.size());
    return exten;

}

/** Set output filename */
std::string SetOutputName(std::string exten, std::string name){
    std::string outputname = name + "_out" + exten;
    return outputname;
}




int main( int argc, char * argv[])
{
    if ( argc < 2)
    {
        std::cerr << "Usage: " << std::endl;
        std::cerr << argv[0] << "  inputImageFile " << std::endl;
        return EXIT_FAILURE;
    }

    /** Get Dimension & extension */

    //Extension
    std::string exten = SetExten(argv[1]);

    //Set output filename
    std::string OutputFile = SetOutputName(exten, argv[2]);


    //Dimension
    int dim = 2;

    if(exten == ".jpeg" || exten == ".jpg" || exten == ".png")
        dim = 2;
    else if(exten == ".mha" || exten == ".mhd" || exten == ".nrrd")
        dim = 3;
    else
    {
        do{
            std::cout<< "Dimension ? "<<std::endl;
            std::cin>>dim;

        }while(dim >3 || dim <2);
    }


    /** Image type */

    if(dim == 2)
    {
        typedef itk::RGBPixel<unsigned char> PixelType;
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
        reader->SetFileName(argv[1]);
        reader->Update();

        /** Filter  */
        filter->SetInput(reader->GetOutput());
        filter->Update();

        /** Writer  */
        writer->SetInput(filter->GetOutput());
        writer->SetFileName(OutputFile);
        writer->Update();

//        QuickView viewer;
//        viewer.AddImage(reader->GetOutput(), true, "Original Image");
//        viewer.AddImage(filter->GetOutput(), true, "Filtered Image");
//        viewer.Visualize();
    }



    else
    {
        typedef itk::RGBPixel<float> PixelType;
        const unsigned int Dimension = 3;

        typedef itk::Image<PixelType, Dimension>        ImageType;
        typedef itk::ImageFileReader<ImageType>         ReaderType;
        typedef itk::ImageFileWriter<ImageType>         WriterType;
        typedef SmoothingFilter<ImageType>              FilterType;

        ReaderType::Pointer reader = ReaderType::New();
        WriterType::Pointer writer = WriterType::New();
        FilterType::Pointer filter = FilterType::New();

        /** Read    */
        reader->SetFileName(argv[1]);
        reader->Update();

        /** Filter  */
        filter->SetInput(reader->GetOutput());
        filter->Update();

        /** Writer  */
        writer->SetInput(filter->GetOutput());
        writer->SetFileName(OutputFile);
        writer->Update();
    }



    return 0;

}
