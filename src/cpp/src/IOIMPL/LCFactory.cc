#include "IOIMPL/LCFactory.h"

#include "IO/LCWriter.h"
#include "IO/LCReader.h"

#include "WriterDecorator.h"
#include "ReaderDecorator.h"

// #include "SIO/SIOWriter.h"
// #include "SIO/SIOReader.h"

// #include "RIO/RIOWriter.h"
// #include "RIO/RIOReader.h"


//fg:  09/2009 - modified to return generic decorators that decide on the io type based on the file 
//     name extension in open()


using namespace IO ;


namespace IOIMPL{

  
  LCFactory::LCFactory(){}
  
  
  LCFactory* LCFactory::getInstance() { 
    
    static LCFactory _me ;
    
    return &_me ;
  }
  
  LCFactory::~LCFactory(){}
  
  
  LCWriter * LCFactory::createLCWriter() { 
    
    
    return new IOIMPL::WriterDecorator ;
    
    //     switch(_writerType ) {
    //     case 'r':
    //       return new RIO::RIOWriter ;
    //       break ;
    //     default :
    //       return new SIO::SIOWriter ;
    //     }
    
  }
  
  LCReader * LCFactory::createLCReader(int lcReaderFlag) {
    
    return new IOIMPL::ReaderDecorator ;
   
//     switch(_readerType ) {
//     case 'r':
//       return new RIO::RIOReader( lcReaderFlag );
//       break;
//     default :
//       return new SIO::SIOReader( lcReaderFlag ) ;
//     }
    
  }
  
  
} // namespace
