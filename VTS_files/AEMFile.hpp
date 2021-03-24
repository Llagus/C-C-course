/***********************************************************************************************//**
 *  Creates Alttitude Ephemeris Message (AEM) files for the description of attitude ephemerides.
 *  @class      AEMFile
 *  @author     Eudald Llagostera Brugarola (ELB), eudald.llagostera@estudiantat.upc.edu
 *  @date       2020-dec-6
 *  @copyright  This file is part of a project developed at Nano-Satellite and Payload Laboratory
 *              (NanoSat Lab), Universitat Politècnica de Catalunya - UPC BarcelonaTech.
 **************************************************************************************************/

#ifndef __AEM_FILE_HPP__
#define __AEM_FILE_HPP__

/* Gloabal include */
#include "dss.hpp"

/* Internal includes*/
#include "Globals.hpp"
#include "Database.hpp"
#include "TimeUtils.hpp"
#include "CICFiles.hpp"

/***********************************************************************************************//**
 * Manages the creation of AEM files. Writtes the AEM file following the CIC/CCSDS protocol.
 **************************************************************************************************/
class AEMFile : public CICFiles
{
public:
    /*******************************************************************************************//**
     * Generates the AEM data file of the spedified satellite id. This file contains
     * orientation ephemerides for a single celestial body. And this ephemerdies can be
     * provided under different forms (Euler angles, quaternion). 
     * 
     * @param id satellite identifier.
     * @param vts_files_path path to where the file is created.
     **********************************************************************************************/
    AEMFile(std::string id, std::string vts_files_path);

protected:

    /*******************************************************************************************//**
     * Writes the Header of the AEM file. It fallows the following structure:
     *     1. Version of the CIC protocol.
     *     2. Creation date
     *     3. Originator
     **********************************************************************************************/
    void setHeader(void);

    /*******************************************************************************************//**
     * Writes the Metadata of the AEM file. The structure that follows is the following one: 
     *     1.  Meta start
     *     2.  Object name
     *     3.  Object id
     *     4.  Center name (origin of the reference frame)
     *     5.  Reference frame A (the value is obligatory: EME2000)
     *     6.  Reference frame B (second reference frame involved in the transformation described)
     *     7.  Attitude direction (Direction of the rotation described) 
     *     8.  Time system (UTC is used)
     *     9.  Attitude type (Quaternion is used)
     *     10. Quaternion type (allows to specify the scalar portion of a quaternion, FIRST is used)
     *     11. Meta stop
     **********************************************************************************************/    
    void setMetadata(void);

    /*******************************************************************************************//**
     * Writes the data of the corresponding AEM file in the text variable.
     * Per each time instant a row has to be created. This row is defined 
     * with the format: EPOCH Q1 Q2 Q3 Q4
     *     - EPOCH is the time instant in UTC
     *     - Q1 represents the real part.
     *     - Q2, Q3, Q4 represents the fundamental quaternion units
     **********************************************************************************************/
    void setData(void);
};

#endif /* __AEM_FILE_HPP__ */
