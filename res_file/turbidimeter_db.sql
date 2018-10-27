-- MySQL dump 10.13  Distrib 5.6.17, for Win64 (x86_64)
--
-- Host: localhost    Database: turbidimeter_db
-- ------------------------------------------------------
-- Server version	5.6.17

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account_tbl`
--

DROP TABLE IF EXISTS `account_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `account_tbl` (
  `uid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `uname` varchar(50) NOT NULL,
  `urealname` varchar(50) NOT NULL,
  `unickname` varchar(20) NOT NULL,
  `ustatus` varchar(10) NOT NULL,
  `ugroupid` int(5) NOT NULL,
  `upassword` varbinary(200) NOT NULL,
  `ufingerprint` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`uid`),
  UNIQUE KEY `uname` (`uname`),
  UNIQUE KEY `unickname` (`unickname`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_tbl`
--

LOCK TABLES `account_tbl` WRITE;
/*!40000 ALTER TABLE `account_tbl` DISABLE KEYS */;
INSERT INTO `account_tbl` VALUES (1,'manager','默认管理员1','管理员1','init',1,'??|????????/?',NULL),(2,'checker','默认技术员','技术员','invalid',2,'fcb47c931c123f8781a4d4fae92ffd19',NULL),(3,'operator','默认实验员','某实验员','invalid',3,'??|????????/?',NULL);
/*!40000 ALTER TABLE `account_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `arrange_setting_tbl`
--

DROP TABLE IF EXISTS `arrange_setting_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `arrange_setting_tbl` (
  `arrange_setting_id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `arrange_setting_name` varchar(50) NOT NULL,
  `arrange_setting_stream` varchar(300) DEFAULT NULL,
  `arrange_setting_type` varchar(20) NOT NULL,
  `arrange_setting_group_num` int(1) NOT NULL,
  `method` varchar(50) NOT NULL,
  `whether_share_std` int(1) NOT NULL,
  `operator_uid` int(1) NOT NULL,
  `show_in_list` int(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`arrange_setting_id`)
) ENGINE=InnoDB AUTO_INCREMENT=58 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `arrange_setting_tbl`
--

LOCK TABLES `arrange_setting_tbl` WRITE;
/*!40000 ALTER TABLE `arrange_setting_tbl` DISABLE KEYS */;
INSERT INTO `arrange_setting_tbl` VALUES (1,'二计量_10组','1-S1,1-S2,1-T1,1-T2,6-S1,6-S2,6-T1,6-T2,2-T2,2-T1,2-S2,2-S1,7-T2,7-T1,7-S2,7-S1,3-S2,3-S1,3-T2,3-T1,8-S2,8-S1,8-T2,8-T1,4-T1,4-T2,4-S1,4-S2,9-T1,9-T2,9-S1,9-S2,5-S1,5-S2,5-T1,5-T2,10-S1,10-S2,10-T1,10-T2','private',10,'0',0,0,1);
/*!40000 ALTER TABLE `arrange_setting_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `device_setting_tbl`
--

DROP TABLE IF EXISTS `device_setting_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `device_setting_tbl` (
  `device_setting_id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `box_name` varchar(50) DEFAULT NULL,
  `box_temperature` varchar(20) DEFAULT NULL,
  `box_shake_time` varchar(10) DEFAULT NULL,
  `box_steady_time` varchar(10) DEFAULT NULL,
  `box_shake_freq` varchar(10) DEFAULT NULL,
  `box_shake_interval` varchar(10) DEFAULT NULL,
  `box_measure_interval` varchar(10) DEFAULT NULL,
  `box_measure_begin_time` varchar(10) DEFAULT NULL,
  `stop_cond_duration` varchar(10) DEFAULT NULL,
  `stop_cond_maxabsorbancy` varchar(10) DEFAULT NULL,
  `stop_cond_minabsorbancy` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`device_setting_id`)
) ENGINE=InnoDB AUTO_INCREMENT=305 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `device_setting_tbl`
--

LOCK TABLES `device_setting_tbl` WRITE;
/*!40000 ALTER TABLE `device_setting_tbl` DISABLE KEYS */;
INSERT INTO `device_setting_tbl` VALUES (1,'培养箱1','37','2','20','20','3','2','0','140','-1','-1');
/*!40000 ALTER TABLE `device_setting_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `group_tbl`
--

DROP TABLE IF EXISTS `group_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `group_tbl` (
  `gid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `gname` varchar(50) NOT NULL,
  `gtype` varchar(10) NOT NULL,
  `method_1_privilage` tinyint(1) DEFAULT NULL,
  `method_2_privilage` tinyint(1) DEFAULT NULL,
  `method_3_privilage` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`gid`),
  UNIQUE KEY `gname` (`gname`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `group_tbl`
--

LOCK TABLES `group_tbl` WRITE;
/*!40000 ALTER TABLE `group_tbl` DISABLE KEYS */;
INSERT INTO `group_tbl` VALUES (1,'管理员','manager',NULL,NULL,NULL),(2,'技术员','checker',NULL,NULL,NULL),(3,'实验员','operator',NULL,NULL,NULL);
/*!40000 ALTER TABLE `group_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `log_tbl`
--

DROP TABLE IF EXISTS `log_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `log_tbl` (
  `logid` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `userid` int(11) NOT NULL,
  `date` date DEFAULT NULL,
  `time` varchar(10) DEFAULT NULL,
  `operation` varchar(2048) DEFAULT NULL,
  `comment` varchar(100) DEFAULT NULL,
  `type` varchar(10) NOT NULL,
  PRIMARY KEY (`logid`)
) ENGINE=InnoDB AUTO_INCREMENT=1519 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `log_tbl`
--

LOCK TABLES `log_tbl` WRITE;
/*!40000 ALTER TABLE `log_tbl` DISABLE KEYS */;
/*!40000 ALTER TABLE `log_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `meta_data`
--

DROP TABLE IF EXISTS `meta_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `meta_data` (
  `mata_data_id` int(1) NOT NULL,
  `db_ver` varchar(20) NOT NULL,
  `last_date` date NOT NULL,
  `last_time` time(1) NOT NULL,
  `backup_type` int(1) NOT NULL,
  `backup_interval` int(1) NOT NULL,
  `backup_time` time(1) NOT NULL,
  `backup_target` varchar(512) NOT NULL,
  `back1` varchar(100) NOT NULL,
  `back2` varchar(100) NOT NULL,
  PRIMARY KEY (`mata_data_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `meta_data`
--

LOCK TABLES `meta_data` WRITE;
/*!40000 ALTER TABLE `meta_data` DISABLE KEYS */;
INSERT INTO `meta_data` VALUES (1,'1.0.0','2018-07-10','23:46:00.0',0,0,'00:00:00.0','0','1','1');
/*!40000 ALTER TABLE `meta_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `raw_data_tbl`
--

DROP TABLE IF EXISTS `raw_data_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `raw_data_tbl` (
  `rawdataid` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `rawdatasn` varchar(20) NOT NULL,
  `timeseq` double DEFAULT NULL,
  `A_stream` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`rawdataid`)
) ENGINE=InnoDB AUTO_INCREMENT=336 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `raw_data_tbl`
--

LOCK TABLES `raw_data_tbl` WRITE;
/*!40000 ALTER TABLE `raw_data_tbl` DISABLE KEYS */;
INSERT INTO `raw_data_tbl` VALUES (1,'1',1,'18.90,21.00,18.95,21.00,18.55,21.30,18.95,20.90,21.25,19.25,21.10,19.25,20.60,19.05,20.85,18.60,21.05,18.60,20.60,18.85,20.85,18.85,20.75,19.10,18.70,21.00,18.90,20.55,19.35,21.30,19.15,21.35,18.95,20.95,18.80,21.10,18.60,20.70,18.75,20.85');
/*!40000 ALTER TABLE `raw_data_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `report_format_tbl`
--

DROP TABLE IF EXISTS `report_format_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `report_format_tbl` (
  `report_format_id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `report_format_name` varchar(20) NOT NULL,
  `level1_items` varchar(200) NOT NULL,
  `sample_info_items` varchar(400) NOT NULL,
  PRIMARY KEY (`report_format_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `report_format_tbl`
--

LOCK TABLES `report_format_tbl` WRITE;
/*!40000 ALTER TABLE `report_format_tbl` DISABLE KEYS */;
INSERT INTO `report_format_tbl` VALUES (1,'','sample_info,raw_data,reliability','sample_name,sample_sn,test_date,report_date');
/*!40000 ALTER TABLE `report_format_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `report_tbl`
--

DROP TABLE IF EXISTS `report_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `report_tbl` (
  `rptid` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `rptsn` varchar(64) NOT NULL,
  `rptname` varchar(64) NOT NULL,
  `test_date` date NOT NULL,
  `sample_name` varchar(50) NOT NULL,
  `test_time` time(1) NOT NULL,
  `measuremethod` varchar(20) NOT NULL,
  `testinfoid` int(10) NOT NULL,
  `test_parameterid` int(10) NOT NULL,
  `test_result_tbl` varchar(20) NOT NULL,
  `test_resultid` int(10) NOT NULL,
  `test_rawdataid_array` varchar(1024) NOT NULL,
  `measure_time_array` varchar(1024) NOT NULL,
  `arrange_setting_id` int(1) unsigned NOT NULL,
  `batch_index` int(1) unsigned NOT NULL,
  `report_path` varchar(512) DEFAULT NULL,
  `report_MD5` varchar(64) DEFAULT NULL,
  `report_status` varchar(64) DEFAULT NULL,
  `report_remark` varchar(64) DEFAULT NULL,
  `report_comment` varchar(64) DEFAULT NULL,
  `device_id` varchar(64) DEFAULT NULL,
  `operator_uid` int(5) NOT NULL,
  `checker_uid` int(1) NOT NULL,
  `manager_uid` int(1) NOT NULL,
  `report_sel_time` varchar(20) NOT NULL,
  `report_format_id` int(1) unsigned NOT NULL,
  `end_style` varchar(20) NOT NULL,
  PRIMARY KEY (`rptid`)
) ENGINE=InnoDB AUTO_INCREMENT=394 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `report_tbl`
--

LOCK TABLES `report_tbl` WRITE;
/*!40000 ALTER TABLE `report_tbl` DISABLE KEYS */;
INSERT INTO `report_tbl` VALUES (1,'','示例','2018-06-18','红霉素试验','14:00:00.0','0',1,1,'',0,'1','1',1,1,'','','4','','','1',1,3,2,'0',1,'');
/*!40000 ALTER TABLE `report_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test_info_tbl`
--

DROP TABLE IF EXISTS `test_info_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `test_info_tbl` (
  `testinfoid` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `sample_name` varchar(64) NOT NULL,
  `sample_sn` varchar(64) DEFAULT NULL,
  `sample_class` varchar(64) DEFAULT NULL,
  `sample_amount` int(10) DEFAULT NULL,
  `sample_specification` varchar(64) DEFAULT NULL,
  `sample_package` varchar(64) DEFAULT NULL,
  `sample_producer` varchar(64) DEFAULT NULL,
  `sample_provider` varchar(64) DEFAULT NULL,
  `test_target` varchar(256) DEFAULT NULL,
  `test_standard` varchar(64) DEFAULT NULL,
  `sample_expiry_date` date DEFAULT NULL,
  `sample_tested_number` int(11) DEFAULT NULL,
  `ambient_temperature` float DEFAULT NULL,
  `ambient_humidity` float DEFAULT NULL,
  `test_date` date DEFAULT NULL,
  `report_date` date DEFAULT NULL,
  `operator_uid` int(10) NOT NULL,
  `checker_uid` int(10) DEFAULT NULL,
  `manager_uid` int(10) DEFAULT NULL,
  PRIMARY KEY (`testinfoid`)
) ENGINE=InnoDB AUTO_INCREMENT=400 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test_info_tbl`
--

LOCK TABLES `test_info_tbl` WRITE;
/*!40000 ALTER TABLE `test_info_tbl` DISABLE KEYS */;
INSERT INTO `test_info_tbl` VALUES (1,'红霉素','T10480248','分类',1,'规格','盒','某制药厂','先驱威锋','出厂检验','CP2015','2020-06-17',1,25,45,'2014-07-01','2014-07-02',0,0,0);
/*!40000 ALTER TABLE `test_info_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test_paramter_tbl`
--

DROP TABLE IF EXISTS `test_paramter_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `test_paramter_tbl` (
  `testparameterid` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `m` int(11) DEFAULT NULL,
  `k` int(11) DEFAULT NULL,
  `Ar` double DEFAULT NULL,
  `r` double DEFAULT NULL,
  `D` double DEFAULT NULL,
  `con_init` double DEFAULT NULL,
  `con_center` double DEFAULT NULL,
  PRIMARY KEY (`testparameterid`)
) ENGINE=InnoDB AUTO_INCREMENT=396 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test_paramter_tbl`
--

LOCK TABLES `test_paramter_tbl` WRITE;
/*!40000 ALTER TABLE `test_paramter_tbl` DISABLE KEYS */;
INSERT INTO `test_paramter_tbl` VALUES (1,10,4,100,2,1,0,0);
/*!40000 ALTER TABLE `test_paramter_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test_shortcut_tbl`
--

DROP TABLE IF EXISTS `test_shortcut_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `test_shortcut_tbl` (
  `test_shortcut_id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `test_shortcut_name` varchar(50) NOT NULL,
  `sample_batch_num` int(1) unsigned NOT NULL DEFAULT '1',
  `report_id_array` varchar(50) NOT NULL,
  `device_setting_id` int(1) NOT NULL,
  `operator_uid` int(1) NOT NULL,
  `show_in_list` int(1) NOT NULL,
  PRIMARY KEY (`test_shortcut_id`)
) ENGINE=InnoDB AUTO_INCREMENT=41 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test_shortcut_tbl`
--

LOCK TABLES `test_shortcut_tbl` WRITE;
/*!40000 ALTER TABLE `test_shortcut_tbl` DISABLE KEYS */;
/*!40000 ALTER TABLE `test_shortcut_tbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `twomeasure_result_tbl`
--

DROP TABLE IF EXISTS `twomeasure_result_tbl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `twomeasure_result_tbl` (
  `rstid` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `I` double DEFAULT NULL,
  `t` double DEFAULT NULL,
  `S2` double DEFAULT NULL,
  `f` int(11) DEFAULT NULL,
  `M` double DEFAULT NULL,
  `R` double DEFAULT NULL,
  `g` double DEFAULT NULL,
  `Sm` double DEFAULT NULL,
  `Rh` double DEFAULT NULL,
  `Rl` double DEFAULT NULL,
  `Pt` double DEFAULT NULL,
  `Ph` double DEFAULT NULL,
  `Pl` double DEFAULT NULL,
  `FL` varchar(10) DEFAULT NULL,
  `F1` varchar(10) DEFAULT NULL,
  `F2` varchar(10) DEFAULT NULL,
  `F3` varchar(10) DEFAULT NULL,
  `F6` varchar(10) DEFAULT NULL,
  `F7` varchar(10) DEFAULT NULL,
  `F1_conc` varchar(40) DEFAULT NULL,
  `F2_conc` varchar(40) DEFAULT NULL,
  `F3_conc` varchar(40) DEFAULT NULL,
  `F6_conc` varchar(40) DEFAULT NULL,
  `F7_conc` varchar(40) DEFAULT NULL,
  `relib_conc` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`rstid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `twomeasure_result_tbl`
--

LOCK TABLES `twomeasure_result_tbl` WRITE;
/*!40000 ALTER TABLE `twomeasure_result_tbl` DISABLE KEYS */;
/*!40000 ALTER TABLE `twomeasure_result_tbl` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-07-11  0:12:20
