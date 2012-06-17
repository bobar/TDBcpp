-- MySQL dump 10.11
--
-- Host: localhost    Database: tdb
-- ------------------------------------------------------
-- Server version	5.0.75-0ubuntu10.5

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
-- Table structure for table `accounts`
--

DROP TABLE IF EXISTS `accounts`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `accounts` (
  `id` int(11) default NULL,
  `trigramme` char(3) default NULL,
  `name` text,
  `first_name` text,
  `nickname` text,
  `casert` tinytext,
  `status` int(11) default NULL,
  `promo` int(11) default NULL,
  `mail` text,
  `picture` text,
  `balance` int(11) default NULL,
  UNIQUE KEY `id` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Not dumping data for table `accounts`
--


--
-- Table structure for table `admins`
--

DROP TABLE IF EXISTS `admins`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `admins` (
  `id` int(11) default NULL,
  `permissions` int(11) default NULL,
  `passwd` tinytext,
  UNIQUE KEY `id` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `admins`
--

LOCK TABLES `admins` WRITE;
/*!40000 ALTER TABLE `admins` DISABLE KEYS */;
INSERT INTO `admins` VALUES (2,2,'0fceeba033f12d27d2d77210eb7f8321'),
(869,3,'a668aa66d75b06eab3b20841465a2843'),
(4,2,'823299e0dbcad6c1e15131c322905248'),
(98,2,'11361f90c0f7c7ef2ec207773225b1c4'),
(250,2,'198beed664ce5f107625ca571fd44be4'),
(259,1,'91618c0b026ce98562a1f61d9ddaec6a'),
(1201,1,'deb2919267c91b42595320c619aa22b4'),
(3,2,'46d5e1aa56a9bb01ba3b97e11d17144a'),
(33,1,'c85cf0e8760467f210146df45d078d11'),
(6,2,'8cb4f88ffd80dac9c59859dcea8e2ae4'),
(7,2,'b815d9b7ef43fecce25e3af8e51c601f'),
(506,2,'83c2c671fabaed99f5801b7fcd383a5f'),
(135,3,'b7d72119c8080a3d5458eedcf821c2cf'),
(150,2,'f34c903e17cfeea18e499d4627eeb3ec'),
(532,2,'96d4d752789877153923b6d8b025c08e'),
(1411,1,'62f5150008e7bda8dbf522ffca36a86a'),
(143,2,'f6f4deb7dad1c2e5e0b4d6569dc3c1c5'),
(153,3,'1149318e5eb108c9ba1c2155d06a32f8'),
(228,2,'b15866602b0fd94ce8bda1de55b3efb9'),
(1648,2,'5c6d01587c46060488c56e6484d3e1e9'),
(1528,0,'5c6d01587c46060488c56e6484d3e1e9'),
(1264,3,'4d2b31c91d33a32a98584546736d5c73'),
(1065,3,'64db084f991bc69929c37bfdfad62e60'),
(746,3,'37ade505f5d574491a830cd7aee4d692'),
(872,3,'65e8836b51f71f13b539dad7f84b02a1'),
(264,1,'ed735d55415bee976b771989be8f7005'),
(1029,2,'cd03ee58546a5ace4502526d50a4171e'),
(1047,2,'141eac23ab6d37f0805cb905405fa259'),
(5,2,'d622d8cedf2a7b1a9905a8042d84f5e1'),
(1271,0,'5c6d01587c46060488c56e6484d3e1e9'),
(1495,3,'28208d6349c2b1df123010a08c45d30b'),
(1354,0,'5c6d01587c46060488c56e6484d3e1e9'),
(1400,0,'5c6d01587c46060488c56e6484d3e1e9'),
(1113,2,'e7753d57ff84c355ae230c7d8afe7585'),
(0,3,'a00bbb12dcd8025a482cfaeb9f5cab55'),
(1381,3,'a00bbb12dcd8025a482cfaeb9f5cab55'),
(1085,2,'5c6d01587c46060488c56e6484d3e1e9'),
(1736,2,'1149318e5eb108c9ba1c2155d06a32f8'),
(1229,2,'5c6d01587c46060488c56e6484d3e1e9'),
(1265,2,'37ade505f5d574491a830cd7aee4d692'),
(1636,1,'c22a28486f409f63343ccfcbdf4ddc1c'),
(1367,1,'5760492cbea74bf2aa911143cd4da7c0'),
(1355,1,'8140fa28d9a5536e791c9d9a28a3ab7b');
/*!40000 ALTER TABLE `admins` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `clopes`
--

DROP TABLE IF EXISTS `clopes`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `clopes` (
  `marque` tinytext,
  `prix` int(11) default NULL,
  `quantite` int(11) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `clopes`
--

LOCK TABLES `clopes` WRITE;
/*!40000 ALTER TABLE `clopes` DISABLE KEYS */;
INSERT INTO `clopes` VALUES ('Marlboro Rouge',610,3254),
('Malboro Gold',610,2034),
('Camel',610,3367),
('Lucky Strike',580,1966),
('Philip Morris',610,942),
('Dunhill light',610,175),
('Dunhill',610,699),
('Sachet filtres',240,24),
('OCB Rolls',220,1),
('OCB longues',160,163),
('OCB courtes',140,99),
('Lucky Convertibles',610,7),
('Tabac à rouler',560,2);
/*!40000 ALTER TABLE `clopes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transactions`
--

DROP TABLE IF EXISTS `transactions`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `transactions` (
  `id` int(11) default NULL,
  `price` int(11) default NULL,
  `comment` text,
  `admin` int(11) default NULL,
  `date` int(11) default NULL,
  `id2` int(11) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `transactions`
--

/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-05-27 13:07:57
