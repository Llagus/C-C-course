/***********************************************************************************************//**
 *  Creates Alttitude Ephemeris Message (AEM) files for the description of attitude ephemerides.
 *  @class      AEMFile
 *  @author     Eudald Llagostera Brugarola (ELB), eudald.llagostera@estudiantat.upc.edu
 *  @date       2020-dec-6
 *  @copyright  This file is part of a project developed at Nano-Satellite and Payload Laboratory
 *              (NanoSat Lab), Universitat Politècnica de Catalunya - UPC BarcelonaTech.
 **************************************************************************************************/

#include "AEMFile.hpp"

AEMFile::AEMFile(std::string id, std::string m_vts_files_path)
{
    m_vts_sufix = "AEM_ATTITUDE.txt";
    m_id = id;
    m_cic_name = m_id + m_vts_sufix;
    m_cic_file.open(m_vts_files_path + "Data/" + m_cic_name);
    m_text = "";

    setHeader();
    setMetadata();
    setData(); 

    m_cic_file.close();
}

void AEMFile::setHeader(void)
{
    m_text = "CIC_AEM_VERS = 2.0\n";
    /* File creation date */
    time_t now = time(0);
    std::stringstream buffer;
    buffer << std::put_time(gmtime(&now), "%Y-%m-%dT%H:%M:%S");
    m_text += "CREATION_DATE = " + buffer.str() + "\n";
    /* Originator of the file */
    m_text += "ORIGINATOR = DSS_SIMULATOR\n\n";

    m_cic_file.write(m_text.c_str(), m_text.length());
    m_text = "";
}

void AEMFile::setMetadata(void)
{
    /* Meta-data */
    m_text += "META_START\n";
    /* Name of the object */
    m_text += "OBJECT_NAME = "+ m_id + "\n";
    /* Identifier of the object, it is the same as  the name */
    m_text += "OBJECT_ID = "+ m_id + "\n";
    /* Origin of the reference frame */
    m_text += "CENTER_NAME = EARTH\n";
    /* Reference frame A name mandatory to be 'EME2000' */
    m_text += "REF_FRAME_A = EME2000\n";
    /* Reference frame B */
    m_text += "REF_FRAME_B = SC_BODY_1\n";
    /* Direction of the rotation described */
    m_text += "ATTITUDE_DIR = A2B\n";
    /* Time system for the file dates */
    m_text += "TIME_SYSTEM = UTC\n";
    /* Attitude type */
    m_text += "ATTITUDE_TYPE = QUATERNION\n"; 
    /* Quaternion type*/
    m_text += "QUATERNION_TYPE = FIRST\n";
    /* End of Meta-data*/
    m_text += "META_STOP\n\n";

    m_cic_file.write(m_text.c_str(), m_text.length());
    m_text = "";
}

void AEMFile::setData(void)
{
    /*Satellite attitude data*/
    /* Per each time instant a row has to be created. This row is defined 
     * with the format: EPOCH Q1 Q2 Q3 Q4
     *     - EPOCH is the time instant in UTC
     *     - Q1 represents the real part.
     *     - Q2, Q3, Q4 represents the fundamental quaternion units
     **/
    timeval t_struct;
    timeval referenced_time;
    std::string time_str;
    Database& db = Database::get();
    db.prepareSet("agent=" + m_id + ";keyname=attitude;order=NOT_SET");
    for(DBRow row : db) {
        /* Epoch first */
        t_struct.tv_sec = (int)row.time;
        t_struct.tv_usec = (row.time - t_struct.tv_sec) * 1e6;
        timeradd(&t_struct, &Globals::user.simulation_start_epoch, &referenced_time);
        time_str = TimeUtils::fromUNIXtoString(referenced_time);
        std::replace(time_str.begin(), time_str.end(), ' ', 'T');
        m_text += time_str + " ";
        /* Attitude Q1 Q2 Q3 Q4 */
        m_text += std::to_string(row.value["q1"].GetDouble()) + " ";
        m_text += std::to_string(row.value["q2"].GetDouble()) + " ";
        m_text += std::to_string(row.value["q3"].GetDouble()) + " ";
        m_text += std::to_string(row.value["q4"].GetDouble()) + " ";
        m_text += "\n";
        m_cic_file.write(m_text.c_str(), m_text.length());
        m_text = "";
    }
}
