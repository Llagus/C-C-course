/***********************************************************************************************//**
 *  Creates Missin Ephemeris Message (MEM) files for the description of time-dependent data.
 *  @class      MEMFile
 *  @author     Eudald Llagostera Brugarola (ELB), eudald.llagostera@estudiantat.upc.edu
 *  @date       2020-dec-6
 *  @copyright  This file is part of a project developed at Nano-Satellite and Payload Laboratory
 *              (NanoSat Lab), Universitat Politècnica de Catalunya - UPC BarcelonaTech.
 **************************************************************************************************/

#ifndef __MEM_FILE_HPP__
#define __MEM_FILE_HPP__

/* Gloabal include */
#include "dss.hpp"

/* Internal includes*/
#include "Globals.hpp"
#include "Database.hpp"
#include "TimeUtils.hpp"
#include "CICFiles.hpp"

/***********************************************************************************************//**
 * Manages the creation of MEM files. Writtes the MEM file following the CIC/CCSDS protocol.
 **************************************************************************************************/
class MEMFile : public CICFiles
{
public:
    /*******************************************************************************************//**
     * Generates the MEM data file of the spedified element id. This file contains
     * ephemerides for the quantity in a defined time range.
     * 
     * @param id satellite identifier.
     * @param vts_files_path path to where the file is created.
     * @param protocol name of the protocol specified for the data generated.
     **********************************************************************************************/
    MEMFile(std::string id, std::string vts_files_path, std::string protocol);

protected:

    /*******************************************************************************************//**
     * Writes the Header of the MEM file. It fallows the following structure:
     *     1. Version of the CIC protocol.
     *     2. Creation date
     *     3. Originator
     **********************************************************************************************/
    void setHeader(void);

    /*******************************************************************************************//**
     * Writes the Metadata of the MEM file. The structure that follows is the following one: 
     *     1.  Meta start
     *     2.  Object name
     *     3.  Object id
     *     4.  User defined protocol (Name of the protocol used: CIC)
     *     5.  User defined content (must reference a defined protocol)
     *     6.  Time system (UTC is used)
     *     7.  Meta stop
     * 
     * @param protocol name of the protocol specified for the data generated.
     **********************************************************************************************/    
    void setMetadata(std::string protocol);

    /*******************************************************************************************//**
     * Writes the data of the corresponding MEM file in the text variable.
     * Per each time instant a row has to be created. This row is defined 
     * with the format: EPOCH Data
     *     - EPOCH is the time instant in UTC
     *     - Data correspond to the format defined by the specified protocol for the 
     *       described variable. 
     * 
     * @param protocol name of the protocol specified for the data generated.
     **********************************************************************************************/
    void setData(std::string protocol);
};

#endif /* __MEM_FILE_HPP__ */
