/***********************************************************************************************//**
 *  Creates Mission Parameter Message (MPM) files for the description of time-independent data.
 *  @class      MPMFile
 *  @author     Eudald Llagostera Brugarola (ELB), eudald.llagostera@estudiantat.upc.edu
 *  @date       2020-dec-6
 *  @copyright  This file is part of a project developed at Nano-Satellite and Payload Laboratory
 *              (NanoSat Lab), Universitat Politècnica de Catalunya - UPC BarcelonaTech.
 **************************************************************************************************/

#ifndef __MPM_FILE_HPP__
#define __MPM_FILE_HPP__

/* Gloabal include */
#include "dss.hpp"

/* Internal includes*/
#include "Globals.hpp"
#include "Database.hpp"
#include "TimeUtils.hpp"
#include "CICFiles.hpp"

/***********************************************************************************************//**
 * Manages the creation of MPM files. Writtes the MPM file following the CIC/CCSDS protocol.
 **************************************************************************************************/
class MPMFile : public CICFiles
{
public:
    /*******************************************************************************************//**
     * Generates the MPM data file of the spedified element id. It contains the value of
     * constant paramiters. 
     * 
     * @param id satellite identifier.
     * @param vts_files_path path to where the file is created.
     * @param protocol name of the protocol specified for the data generated.
     **********************************************************************************************/
    MPMFile(std::string id, std::string vts_files_path, std::string protocol);

protected:

    /*******************************************************************************************//**
     * Writes the Header of the MPM file. It fallows the following structure:
     *     1. Version of the CIC protocol.
     *     2. Creation date
     *     3. Originator
     **********************************************************************************************/
    void setHeader(void);

    /*******************************************************************************************//**
     * Writes the Metadata of the MPM file. The structure that follows is the following one: 
     *     1.  Meta start
     *     2.  Object name
     *     3.  Object id
     *     4.  User defined protocol (Name of the protocol used: CIC)
     *     5.  User defined content (must reference a defined protocol)
     *     7.  Meta stop
     **********************************************************************************************/    
    void setMetadata(std::string protocol);

    /*******************************************************************************************//**
     * Writes the data of the corresponding MPM file in the text variable.
     * The format for entering the data in MPM files is DATA = Data. 
     *     - Data correspond to the format defined by the specified protocol for the 
     *       described variable. 
     **********************************************************************************************/
    void setData(std::string protocol);
};

#endif /* __MPM_FILE_HPP__ */
