INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 6 AND date_to IS NULL;

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 7 AND date_to IS NULL;

UPDATE afe_ext
SET sipm_id = 6,
	sipm_date_from = (SELECT date_from FROM sipm WHERE id = 6)
WHERE
	id = 3
	
UPDATE afe_main
SET sipm_id = 7,
	sipm_date_from = (SELECT date_from FROM sipm WHERE id = 7)
WHERE
	id = 4
	
INSERT INTO bar(id, number, afe_main_id, afe_main_date_from, scintillator_id, scintillator_date_from, afe_ext_id, afe_ext_date_from) 
SELECT max(id) + 1, 'AFE17', 4,  (SELECT date_from FROM afe_main WHERE id = 4), 5, (SELECT date_from FROM scintillator WHERE id = 5), 3, (SELECT date_from FROM afe_ext WHERE id = 3) FROM bar;

UPDATE device
SET purchase_date = '2021-05-31'
WHERE serial_number IN ('2104160PW0020A0101', '2104160PW0020A0104', '2104160PW0006A0101', '2104160PW0006A0105')

UPDATE device
SET location_id = 1

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), "2104160PW0020A0102", '2021-05-31', 1 FROM device;

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), "2104160PW0020A0103", '2021-05-31', 1 FROM device;

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), "2104160PW0020A0105", '2021-05-31', 1 FROM device;

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), "2104160PW0020A0106", '2021-05-31', 1 FROM device;

INSERT INTO afe_main(id, date_from) 
SELECT id, date_from FROM device WHERE id = 8 AND date_to IS NULL;

INSERT INTO afe_main(id, date_from) 
SELECT id, date_from FROM device WHERE id = 9 AND date_to IS NULL;


INSERT INTO afe_main(id, date_from) 
SELECT id, date_from FROM device WHERE id = 10 AND date_to IS NULL;

INSERT INTO afe_main(id, date_from) 
SELECT id, date_from FROM device WHERE id = 11 AND date_to IS NULL;

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), "2104160PW0007A0101", '2021-05-31', 1 FROM device;

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), "2104160PW0007A0102", '2021-05-31', 1 FROM device;

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), "2104160PW0007A0103", '2021-05-31', 1 FROM device;

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), "2104160PW0007A0104", '2021-05-31', 1 FROM device

INSERT INTO hub(id, date_from) 
SELECT id, date_from FROM device WHERE id = 16 AND date_to IS NULL;

INSERT INTO hub(id, date_from) 
SELECT id, date_from FROM device WHERE id = 17 AND date_to IS NULL;

INSERT INTO hub(id, date_from) 
SELECT id, date_from FROM device WHERE id = 18 AND date_to IS NULL;

INSERT INTO hub(id, date_from) 
SELECT id, date_from FROM device WHERE id = 19 AND date_to IS NULL;

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4710', '2021-05-31', 1, '2104160PW0008A0101' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4711', '2021-05-31', 1, '2104160PW0008A0102' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4712', '2021-05-31', 1, '2104160PW0008A0103' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4713', '2021-05-31', 1, '2104160PW0008A0104' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4714', '2021-05-31', 1, '2104160PW0008A0105' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4715', '2021-05-31', 1, '2104160PW0008A0106' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4709', '2021-05-31', 1, '2104160PW0008A0107' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4708', '2021-05-31', 1, '2104160PW0008A0108' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4707', '2021-05-31', 1, '2104160PW0008A0109' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4706', '2021-05-31', 1, '2104160PW0008A0110' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4705', '2021-05-31', 1, '2104160PW0008A0111' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'SN4704', '2021-05-31', 1, '2104160PW0008A0112' FROM device

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 21 AND date_to IS NULL;

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 22 AND date_to IS NULL;

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 23 AND date_to IS NULL

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 24 AND date_to IS NULL

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 25 AND date_to IS NULL

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 26 AND date_to IS NULL

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 27 AND date_to IS NULL

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 28 AND date_to IS NULL

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 29 AND date_to IS NULL

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 30 AND date_to IS NULL

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 31 AND date_to IS NULL

UPDATE sipm
SET v_br = 52.10,
	v_op = 55.1,
	dark_current = 0.646
WHERE id = 6

UPDATE sipm
SET v_br = 52.03,
	v_op = 55.03,
	dark_current = 0.577
WHERE id = 7

UPDATE sipm
SET v_br = 52.09,
	v_op = 55.09,
	dark_current = 0.649
WHERE id = 20

UPDATE sipm
SET v_br = 52.14,
	v_op = 55.14,
	dark_current = 0.658
WHERE id = 21

UPDATE sipm
SET v_br = 52.14,
	v_op = 55.14,
	dark_current = 0.688
WHERE id = 22

UPDATE sipm
SET v_br = 52.15,
	v_op = 55.15,
	dark_current = 0.585
WHERE id = 23

UPDATE sipm
SET v_br = 52.27,
	v_op = 55.27,
	dark_current = 0.665
WHERE id = 24

UPDATE sipm
SET v_br = 52.19,
	v_op = 55.19,
	dark_current = 0.692
WHERE id = 25

UPDATE sipm
SET v_br = 52.15,
	v_op = 55.15,
	dark_current = 0.675
WHERE id = 26

UPDATE sipm
SET v_br = 52.20,
	v_op = 55.20,
	dark_current = 0.706
WHERE id = 27

UPDATE sipm
SET v_br = 52.18,
	v_op = 55.18,
	dark_current = 0.601
WHERE id = 28

UPDATE sipm
SET v_br = 52.11,
	v_op = 55.11,
	dark_current = 0.602
WHERE id = 29

UPDATE sipm
SET v_br = 52.02,
	v_op = 55.02,
	dark_current = 0.643
WHERE id = 30

UPDATE sipm
SET v_br = 52.14,
	v_op = 55.14,
	dark_current = 0.593
WHERE id = 31

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'do ustalenia', '2021-05-31', 1, '2104160PW0009A0101' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'do ustalenia', '2021-05-31', 1, '2104160PW0009A0102' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'do ustalenia', '2021-05-31', 1, '2104160PW0009A0103' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'do ustalenia', '2021-05-31', 1, '2104160PW0009A0104' FROM device

INSERT INTO device(id, date_from, serial_number, purchase_date, location_id, comments) 
SELECT max(id) + 1, CAST((julianday('now') - 2440587.5)*86400000 AS INTEGER), 'do ustalenia', '2021-05-31', 1, '2104160PW0009A0105' FROM device

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 32 AND date_to IS NULL;

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 33 AND date_to IS NULL;

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 34 AND date_to IS NULL;

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 35 AND date_to IS NULL;

INSERT INTO sipm(id, date_from) 
SELECT id, date_from FROM device WHERE id = 36 AND date_to IS NULL;