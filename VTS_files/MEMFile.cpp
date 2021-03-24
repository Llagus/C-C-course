/***********************************************************************************************//**
 *  Creates Missin Ephemeris Message (MEM) files for the description of time-dependent data.
 *  @class      MEMFile
 *  @author     Eudald Llagostera Brugarola (ELB), eudald.llagostera@estudiantat.upc.edu
 *  @date       2020-dec-6
 *  @copyright  This file is part of a project developed at Nano-Satellite and Payload Laboratory
 *              (NanoSat Lab), Universitat Politècnica de Catalunya - UPC BarcelonaTech.
 **************************************************************************************************/

#include "MEMFile.hpp"

MEMFile::MEMFile(std::string id, std::string vts_file_path, std::string protocol)
{
    m_vts_sufix = "MEM_" + protocol + ".txt";
    m_id = id; 
    m_cic_name = m_id + m_vts_sufix; 
    m_cic_file.open(vts_file_path + "Data/" + m_cic_name);
    m_text = ""; 

    setHeader();
    setMetadata(protocol);
    setData(protocol);

    m_cic_file.close();

}

void MEMFile::setHeader(void)
{
    m_text = "CIC_MEM_VERS = 2.0\n";
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

void MEMFile::setMetadata(std::string protocol)
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

void MEMFile::setData(std::string)
{
    /* TODO: Not defined yet the protocols to implement using the MEM files
     * Depending on the protocol there will be one structure or another.
     * The DSS simulator does not specify and store the values of the defined protocols.
     * 
     * Possible protocols are:
     *     1. SIMULATION_TIME
     *     2. SATELLITE_MODES
     *     3. GEOGRAPHICAL_COORDINATES (Satellite geographical coordinates)
     *     4. SATELLITE_ALTITUDE (Satellite geodetic altitude)
     *     5. BETA_ANGLE (Beta angle)
     *     6. SUN_DIRECTION-SATELLITE_FRAME (Sun direction in the satellite reference frame)
     *     7. SUN_DIRECTION-ORBITAL_FRAME (Sun direction in the local orbital reference frame)
     *     8. MOON_DIRECTION-SATELLITE_FRAME (Moon direction in the satellite reference frame)
     *     9. EARTH_DIRECTION-SATELLITE_FRAME (Earth direction in the satellite reference frame)
     *     10.SATELLITE_ECLIPSE
     *     11.SUN_VISIBILITY 
     *     12.SATELLITE_LOCAL_TIME
     *     13.MEAN_ARGUMENT_OF_LATITUDE
     *     14.SUN_ANGLE_SA_1
     *     15.EARTH_ANGLE_SA_1
     *     16.ROTATION_ANGLE_SA_1
     *     17.ORBIT_NUMBER
     *     18.GEOMETRICAL_VISIBILITY_GROUND_STATION_1
     *     19.MESH_TYPE (Type of over-flown mesh)
     *     20.HOT_SPOT
     *     21.SUN_GLINT
     *     22.SATELLITE_ATTITUDE_MODE
     *     23.SATELLITE_ANGULAR_VELOCITY
     *     24.SATELLITE_ANGULAR_ACCELERATION
     *     25.WHEELS_TORQUES
     *     26.SOLAR_FLUX
     *     27.ALBEDO_FLUX
     *     28.EARTH_FLUX
     *     29.SATELLITE_CONSUMED_POWER
     *     30.BATTERY_VOLTAGE
     *     31.BATTERY_CURRENT
     *     32.SOLAR_ARRAY_CURRENT
     *     33.BATTERY_DOD
     *     34.RF_LINK_GROUND_STATION_1
     *     35.LINE_OF_SIGHT_GROUND_STATION_1-SATELLITE_FRAME
     *     36.LINE_OF_SIGHT_GROUND_STATION_1-STATION_FRAME
     *     37.DISTANCE_GROUND_STATION_1
     *     38.TM_RF_MARGIN_GROUND_STATION_1
     **/

}
