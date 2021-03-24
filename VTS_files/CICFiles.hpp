/***********************************************************************************************//**
 *  Creates files that use the Centre d'Ingénierie Concourante (CIC) protocol.
 *  This files use the CCSDS reference format. 
 *  @class      CICFiles
 *  @author     Eudald Llagostera Brugarola (ELB), eudald.llagostera@estudiantat.upc.edu
 *  @date       2020-dec-6
 *  @copyright  This file is part of a project developed at Nano-Satellite and Payload Laboratory
 *              (NanoSat Lab), Universitat Politècnica de Catalunya - UPC BarcelonaTech.
 **************************************************************************************************/

#ifndef __CIC_FILES_HPP__
#define __CIC_FILES_HPP__

/* Gloabal include */
#include "dss.hpp"

/* Internal includes*/
#include "Globals.hpp"
#include "Database.hpp"
#include "TimeUtils.hpp"

/***********************************************************************************************//**
 * Abstract class that instantiates the attributes and the functions that are common in all the
 * modalities of the CIC files (OEM, AEM, MEM, MPM).
 **************************************************************************************************/
class CICFiles
{
protected:
    std::string m_cic_name;     /*< File name of the CIC file to generate */
    std::string m_vts_sufix;    /*< Sufix of the file name */
    std::string m_id;           /*< Id of the element to register in the CIC file */
    std::string m_text;         /*< Variable where will be stored all the data of the CIC file */
    std::ofstream m_cic_file;   /*< File where the information is written */
    std::string m_time_str;     /*< Time to be written in the file */

    /*******************************************************************************************//**
     * Writes the Header of the CIC file. It starts setting up the version of the CIC protocol.
     * Afterwards it sets the date of the creation, and finaly the originator of the file.
     **********************************************************************************************/
    void setHeader(void);

    /*******************************************************************************************//**
     * Writes the Metadata of the CIC file. Every different file has a different structure of 
     * the metadata. 
     **********************************************************************************************/    
    void setMetadata(void);

    /*******************************************************************************************//**
     * Writes the data of the corresponding CIC file in the text variable.
     **********************************************************************************************/
    void setData(void);

public: 
    
    /******************************************************************************************//**
     * Getters of the protected variables.
     *********************************************************************************************/
    std::string getID(void) {return m_id;}
    std::string getSufix(void) {return m_vts_sufix;}
    std::string getFileName(void) {return m_cic_name;}
    std::string getTime(void) {return m_time_str;}
};

#endif /* __CIC_FILES_HPP__ */
