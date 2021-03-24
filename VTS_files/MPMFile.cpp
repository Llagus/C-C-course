***********************************************************************************************//**
 *  Creates Mission Parameter Message (MPM) files for the description of time-independent data.
 *  @class      MPMFile
 *  @author     Eudald Llagostera Brugarola (ELB), eudald.llagostera@estudiantat.upc.edu
 *  @date       2020-dec-6
 *  @copyright  This file is part of a project developed at Nano-Satellite and Payload Laboratory
 *              (NanoSat Lab), Universitat Politècnica de Catalunya - UPC BarcelonaTech.
 **************************************************************************************************/

#include "MPMFile.hpp"

MPMFile::MPMFile(std::string id, std::string vts_files_path, std::string protocol)
{
 m_vts_sufix = "MPM_" + protocol + ".txt";
    m_id = id; 
    m_cic_name = m_id + m_vts_sufix; 
    m_cic_file.open(vts_files_path + "Data/" + m_cic_name);
    m_text = ""; 

    setHeader();
    setMetadata(protocol);
    setData(protocol);

    m_cic_file.close();
}

void MPMFile::setHeader(void)
{
    m_text = "CIC_MPM_VERS = 2.0\n";
    /* File creation date (e.g. 2009-12-08T09:00:00) */
    time_t now = time(0);
    std::stringstream buffer;
    buffer << std::put_time(gmtime(&now), "%Y-%m-%dT%H:%M:%S");
    m_text += "CREATION_DATE = " + buffer.str() + "\n";
    /* Originator of the file */
    m_text += "ORIGINATOR = DSS-SIMULATOR\n\n";

    m_cic_file.write(m_text.c_str(), m_text.length());
    m_text = "";
}

void MPMFile::setMetadata(std::string protocol)
{
    /* Meta-data */
    m_text += "META_START\n";
    /* Name of the object */
    m_text += "OBJECT_NAME = " + m_id + "\n";
    /* Identifier of the object, it is the same than the name */
    m_text += "OBJECT_ID = " + m_id + "\n";
    /* Protocol used in the ephemerides it will be CIC */
    m_text += "USER_DEFINED_PROTOCOL = CIC\n";
    /* Reference frame name (mandatory to be 'EME2000') */
    m_text += "USER_DEFINED_CONTENT = " + protocol + "\n";
    /* Time system for the file dates */
    m_text += "TIME_SYSTEM = UTC\n";
    /* End of Meta-data */
    m_text += "META_STOP\n\n";

    m_cic_file.write(m_text.c_str(), m_text.length());
    m_text = "";
}

void MPMFile::setData(std::string )
{
    /* TODO: Not defined yet the protocols to implement using the MEM files
     * Depending on the protocol there will be one structure or another.
     * The DSS simulator does not specify and store the values of the defined protocols.
     * 
     * Possible protocols are: 
     *     1. SATELLITE_COORDINATE_SYSTEM (Satellite coordinate system)
     *     2. CENTER_OF_GRAVITY (Satellite centre of gravity)
     *     3. CENTER_OF_ROTATION_SA_1 (Centre of rotation for solar array 1)
     *     4. AXIS_OF_ROTATION_SA_1 (Axis of rotation for solar array 1)
     *     5. REFERENCE_POSITION_SA_1 (Reference position for solar array 1) 
     **/
}
