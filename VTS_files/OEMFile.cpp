/***********************************************************************************************//**
 *  Creates Orbit Ephemeris Message (OEM) files for the description of position ephemerides.
 *  @class      OEMFile
 *  @author     Eudald Llagostera Brugarola (ELB), eudald.llagostera@estudiantat.upc.edu
 *  @date       2020-dec-6
 *  @copyright  This file is part of a project developed at Nano-Satellite and Payload Laboratory
 *              (NanoSat Lab), Universitat Politècnica de Catalunya - UPC BarcelonaTech.
 **************************************************************************************************/

#include "OEMFile.hpp"
LOG_COMPONENT_DEFINE("OEMFile");

OEMFile::OEMFile(std::string id, std::string vts_files_path)
{
    m_vts_sufix = "OEM_POSITION.txt";
    m_id = id; 
    m_cic_name = m_id + m_vts_sufix; 
    m_cic_file.open(vts_files_path + "Data/" + m_cic_name);
    m_text = ""; 

    setHeader();
    setMetadata();
    setData();

    m_cic_file.close();
}

void OEMFile::setHeader(void)
{
    m_text = "CIC_OEM_VERS = 2.0\n";
    /* File creation date (e.g. 2009-12-08T09:00:00) */
    time_t now = time(0);
    std::stringstream buffer;
    buffer << std::put_time(gmtime(&now), "%Y-%m-%dT%H:%M:%S");
    m_text += "CREATION_DATE = " + buffer.str() + "\n";
    /* Originator of the file */
    m_text += "ORIGINATOR = DSS-SIMULATOR\n\n";

    m_cic_file.write(m_text.c_str(), m_text.length());
    m_text = "";
    LOG_INFO("Header writen");
}

void OEMFile::setMetadata(void)
{
    /* Meta-data */
    m_text += "META_START\n";
    /* Name of the object */
    m_text += "OBJECT_NAME = " + m_id + "\n";
    /* Identifier of the object, it is the same than the name */
    m_text += "OBJECT_ID = " + m_id + "\n";
    /* Origin of the reference frame */
    m_text += "CENTER_NAME = EARTH\n";
    /* Reference frame name (mandatory to be 'EME2000') */
    m_text += "REF_FRAME = EME2000\n";
    /* Time system for the file dates */
    m_text += "TIME_SYSTEM = UTC\n";
    /* End of Meta-data */
    m_text += "META_STOP\n\n";

    m_cic_file.write(m_text.c_str(), m_text.length());
    m_text = "";
    LOG_INFO("Metadata writen");

}

void OEMFile::setData(void)
{
    /* Satellite data */
    /* Per each time instant a row has to be created. This row is defined
     * with the format: EPOCH X Y Z X_DOT Y_DOT Z_DOT
     *      - EPOCH is the time instant in UTC
     *      - X, Y, and Z represent the satellite position in ECI
     *      - X_DOT, Y_DOT, and Z_DOT represent the satellite velocity in ECI
     **/
    timeval t_struct;
    timeval referenced_time;
    std::string time_str;
    Database& db = Database::get();
    std::string query = "agent=" + m_id + ";keyname=propagation";
    LOG_INFO("%s", query.c_str());
    db.prepareSet(query);
    LOG_INFO("Set size %d", db.resultSetSize());
    for(DBRow row : db) {
        /* Epoch first */
        t_struct.tv_sec = (int)row.time;
        t_struct.tv_usec = (row.time - t_struct.tv_sec) * 1e6;
        timeradd(&t_struct, &Globals::user.simulation_start_epoch, &referenced_time);
        time_str = TimeUtils::fromUNIXtoString(referenced_time);
        std::replace(time_str.begin(), time_str.end(), ' ', 'T');
        m_text += time_str + " ";
        /* Position: X Y Z in km */
        m_text += std::to_string(row.value["px"].GetDouble() / 1e3) + " ";
        m_text += std::to_string(row.value["py"].GetDouble() / 1e3) + " ";
        m_text += std::to_string(row.value["pz"].GetDouble() / 1e3) + " ";
        /* Velocity: X Y Z in km/s */
        m_text += std::to_string(row.value["vx"].GetDouble() / 1e3) + " ";
        m_text += std::to_string(row.value["vy"].GetDouble() / 1e3) + " ";
        m_text += std::to_string(row.value["vz"].GetDouble() / 1e3) + " ";
        /* New line */
        m_text += "\n";
        m_cic_file.write(m_text.c_str(), m_text.length());
        m_text = "";
    }
}
