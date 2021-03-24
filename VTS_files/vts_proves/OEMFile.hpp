/***********************************************************************************************//**
 *  Creates Orbit Ephemeris Message (OEM) files for the description of position ephemerides.
 *  @class      OEMFile
 *  @author     Eudald Llagostera Brugarola (ELB), eudald.llagostera@estudiantat.upc.edu
 *  @date       2020-dec-6
 *  @copyright  This file is part of a project developed at Nano-Satellite and Payload Laboratory
 *              (NanoSat Lab), Universitat Politècnica de Catalunya - UPC BarcelonaTech.
 **************************************************************************************************/

#ifndef __OEM_FILE_HPP__
#define __OEM_FILE_HPP__


#include "CICFiles.hpp"

/***********************************************************************************************//**
 * Manages the creation of OEM files. Writes the OEM file following the CIC/CCSDS protocol.
 **************************************************************************************************/
class OEMFile : public CICFiles
{
public:
    /*******************************************************************************************//**
     * Generates the OEM data file of the spedified satellite id. This file contains the entire 
     * positions (in ECI) of the satellite that matched with the input id. 
     * 
     * @param id satellite identifier
     * @param vts_files_path path to where the file is created
     **********************************************************************************************/
    OEMFile(std::string id, std::string vts_files_path);

protected:

    /*******************************************************************************************//**
     * Writes the Header of the OEM file. It starts setting up the version of the CIC protocol.
     * Afterwards it sets the date of the creation, and finaly the originator of the file.
     **********************************************************************************************/
    void setHeader(void);

    /*******************************************************************************************//**
     * Writes the Metadata of the OEM file. The structure that follows is the following one: 
     *     1. Meta start
     *     2. Object name
     *     3. Object id.
     *     4. Center name (origin of the reference frame)
     *     5. Reference frame (the value is obligatory: EME2000)
     *     6. Time system (UTC is used)
     *     7. Meta stop
     **********************************************************************************************/    
    void setMetadata(void);

    /*******************************************************************************************//**
     * Writes the data of the corresponding OEM file in the text variable.
     * Per each time instant a row has to be created. This row is defined 
     * with the format: EPOCH X Y Z X_DOT Y_DOT Z_DOT
     *     - EPOCH is the time instant in UTC
     *     - X, Y, and Z represent the satellite position in ECI
     *     - X_DOT, Y_DOT, and Z_DOT represent the satellite velocity in ECI
     **********************************************************************************************/
    void setData(void);
};

#endif /* __OEM_FILE_HPP__ */
