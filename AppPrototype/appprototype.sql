-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Apr 19, 2023 at 04:45 PM
-- Server version: 10.4.28-MariaDB
-- PHP Version: 8.2.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `appprototype`
--

-- --------------------------------------------------------

--
-- Table structure for table `qr_data`
--

CREATE TABLE `qr_data` (
  `id` int(11) NOT NULL,
  `gen_by` text NOT NULL,
  `nr_no` tinyint(4) NOT NULL,
  `nr_name` text NOT NULL,
  `nr_ic` text NOT NULL,
  `nr_phone` varchar(300) NOT NULL,
  `start_date` datetime NOT NULL,
  `end_date` datetime NOT NULL,
  `QR_id` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `qr_validity`
--

CREATE TABLE `qr_validity` (
  `id` int(11) NOT NULL,
  `QR_id` text NOT NULL,
  `start_date` datetime NOT NULL,
  `end_date` datetime NOT NULL,
  `counter` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `user_data`
--

CREATE TABLE `user_data` (
  `id` int(11) NOT NULL,
  `name` text NOT NULL,
  `email` text NOT NULL,
  `ic_num` text NOT NULL,
  `password` text NOT NULL,
  `permission` tinyint(1) NOT NULL,
  `apikey` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `user_data`
--

INSERT INTO `user_data` (`id`, `name`, `email`, `ic_num`, `password`, `permission`, `apikey`) VALUES
(1, 'test', 'test', 'test', '$2y$10$a2AmUeTGLXPXTLgMwHxFVeVfwKCWDLp7.W5fmsPaLun/17S2w.QWe', 1, '68909b36f571f8fe49fdb6295a6f0174c97dc68d5a7a5e'),
(2, 'a', 'a', 'a', '$2y$10$TiCnTbdYpoHQN15yWeoIn.pUQBJEnEZ48xfXSTZ3oOP/B237Lozrq', 0, '');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `qr_data`
--
ALTER TABLE `qr_data`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `qr_validity`
--
ALTER TABLE `qr_validity`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `user_data`
--
ALTER TABLE `user_data`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `email` (`email`) USING HASH;

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `qr_data`
--
ALTER TABLE `qr_data`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `qr_validity`
--
ALTER TABLE `qr_validity`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `user_data`
--
ALTER TABLE `user_data`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
