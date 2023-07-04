-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jul 04, 2023 at 06:32 AM
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

--
-- Dumping data for table `qr_data`
--

INSERT INTO `qr_data` (`id`, `gen_by`, `nr_no`, `nr_name`, `nr_ic`, `nr_phone`, `start_date`, `end_date`, `QR_id`) VALUES
(1, 'test', 4, 'test', 'test', 'test', '2023-04-19 22:51:08', '2023-04-20 22:51:08', '4lj4dtsnuf2d'),
(2, 'test', 4, 'test', '000523415264', '0128628977', '2023-04-25 16:54:17', '2023-04-26 16:54:17', 'qekorh2d10tv'),
(3, 'test', 6, 'hrhr', '136156733521345', 'afdghafh4t', '2023-04-25 19:37:39', '2023-04-26 19:37:39', '3nn0r5nm0ich'),
(4, 'test', 1, 'hehe', 'hehe', 'hehe', '2023-05-02 10:25:53', '2023-05-03 10:25:53', 'yvas61900057'),
(5, 'a', 2, 'uahfa', '8392ytu9ih', 'ewrgwerh', '2023-05-02 12:46:47', '2023-05-03 12:46:47', 'mx1s9my9w72b'),
(6, 'test', 18, 'liewzihao', '05232000', '0128628711', '2023-05-29 11:32:07', '2023-05-30 11:32:07', 'q35ghbu6d6fy');

-- --------------------------------------------------------

--
-- Table structure for table `qr_log`
--

CREATE TABLE `qr_log` (
  `id` int(11) NOT NULL,
  `QR_id` text NOT NULL,
  `start_date` datetime NOT NULL,
  `end_date` datetime NOT NULL,
  `entry_date` datetime NOT NULL,
  `exit_date` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `qr_log`
--

INSERT INTO `qr_log` (`id`, `QR_id`, `start_date`, `end_date`, `entry_date`, `exit_date`) VALUES
(1, 'q35ghbu6d6fy', '2023-05-29 11:32:07', '2023-05-30 11:32:07', '2023-05-29 11:58:38', '2023-05-29 11:59:08'),
(2, 'q35ghbu6d6fy', '2023-05-29 11:32:07', '2023-05-30 11:32:07', '0000-00-00 00:00:00', '2023-05-29 11:59:08');

-- --------------------------------------------------------

--
-- Table structure for table `qr_validity`
--

CREATE TABLE `qr_validity` (
  `id` int(11) NOT NULL,
  `QR_id` text NOT NULL,
  `start_date` datetime NOT NULL,
  `end_date` datetime NOT NULL,
  `counter` tinyint(1) NOT NULL,
  `status` varchar(300) NOT NULL,
  `used_by` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `qr_validity`
--

INSERT INTO `qr_validity` (`id`, `QR_id`, `start_date`, `end_date`, `counter`, `status`, `used_by`) VALUES
(1, '4lj4dtsnuf2d', '2023-04-19 22:51:08', '2023-04-27 22:51:08', 1, 'Used', '2023-04-25 16:50:34'),
(2, 'qekorh2d10tv', '2023-04-25 16:54:17', '2023-04-26 16:54:17', 1, 'Used', '2023-04-25 18:53:11'),
(3, '3nn0r5nm0ich', '2023-04-25 19:37:39', '2023-04-26 19:37:39', 0, 'Expired', '0000-00-00 00:00:00'),
(4, 'yvas61900057', '2023-05-02 10:25:53', '2023-05-03 10:25:53', 0, '', '0000-00-00 00:00:00'),
(5, 'mx1s9my9w72b', '2023-05-02 12:46:47', '2023-05-03 12:46:47', 0, '', '0000-00-00 00:00:00'),
(6, 'q35ghbu6d6fy', '2023-05-29 11:32:07', '2023-05-30 11:32:07', 1, 'Used', '2023-05-29 11:59:08');

-- --------------------------------------------------------

--
-- Table structure for table `rfid_log`
--

CREATE TABLE `rfid_log` (
  `id` int(11) NOT NULL,
  `uid` varchar(300) NOT NULL,
  `entry_date` datetime NOT NULL,
  `exit_date` datetime NOT NULL,
  `status_log` varchar(300) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `rfid_user`
--

CREATE TABLE `rfid_user` (
  `id` int(11) NOT NULL,
  `name` varchar(300) NOT NULL,
  `uid` varchar(300) NOT NULL,
  `last_used` datetime NOT NULL,
  `status` varchar(300) NOT NULL
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
(1, 'test', 'test', 'test', '$2y$10$a2AmUeTGLXPXTLgMwHxFVeVfwKCWDLp7.W5fmsPaLun/17S2w.QWe', 1, 'a433f79bf582f1f317779adca2d896e71831a9e9745050'),
(2, 'a', 'a', 'a', '$2y$10$TiCnTbdYpoHQN15yWeoIn.pUQBJEnEZ48xfXSTZ3oOP/B237Lozrq', 1, '');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `qr_data`
--
ALTER TABLE `qr_data`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `qr_log`
--
ALTER TABLE `qr_log`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `qr_validity`
--
ALTER TABLE `qr_validity`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `rfid_log`
--
ALTER TABLE `rfid_log`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `uid` (`uid`);

--
-- Indexes for table `rfid_user`
--
ALTER TABLE `rfid_user`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `uid` (`uid`);

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
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `qr_log`
--
ALTER TABLE `qr_log`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `qr_validity`
--
ALTER TABLE `qr_validity`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `rfid_log`
--
ALTER TABLE `rfid_log`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `rfid_user`
--
ALTER TABLE `rfid_user`
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
