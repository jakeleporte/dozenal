-- +AMDG

function donedate(element)
	for key,val in pairs(usedvals) do
		if (val == element) then
			return true
		end
	end
	return false
end

function move_from_sun(jdn)
	if (dow_from_jdn(jdn) == 0) then
		return jdn+1
	else
		return jdn
	end
end

function ifinret(element)
	local i = 1
	local j = 0
	for i = #returntab,1,-1 do
		local v = returntab[i]
		for key,val in pairs(v) do
			if (key == "START_DATE") then
				if (val == element) then
					j = i
					break;
				end
			end
		end
	end
	if (j ~= 0) then
		table.remove(returntab,j)
	end
end

function greg_to_jdn(year,month,day)
	local a = math.floor((14 - month) / 12)
	local y = year + 4800 - a
	local m = month + (12 * a) - 3
	local jdn = day + math.floor(((153 * m) + 2) / 5) + (365 * y) + 
		math.floor(y / 4) - math.floor(y / 100) + 
		math.floor(y / 400) - 32045
	return jdn
end

function jdn_to_greg(jdn)
	local Q = jdn + 0.5
	local Z = math.floor(Q)
	local W = math.floor((Z - 1867216.25) / 36524.25)
	local X = math.floor(W / 4)
	local A = Z + 1 + W - X
	local B = A + 1524
	local C = math.floor((B - 122.1) / 365.25)
	local D = math.floor(365.25 * C)
	local E = math.floor((B - D) / 30.6001)
	local F = math.floor(30.6001 * E)
	dy = B - D - F + (Q - Z)
	mn = E - 1
	if (mn > 12) then
		mn = E - 13
	end
	if ((mn == 1) or (mn == 2)) then
		yr = C - 4715
	else
		yr = C - 4716
	end
	return math.floor(yr), math.floor(mn), math.floor(dy)
end

function dozenize(num)
	local n = math.floor(num)
	local digits = "0123456789XE"
	local t = {}
	repeat
		local d = (n % 12) + 1
		n = math.floor(n / 12)
		table.insert(t,1,digits:sub(d,d))
	until n == 0
	return table.concat(t,"")
end

function last_char(s)
	if (string.sub(dozenize(s),-1,-1) == "1") then
		return "st"
	elseif (string.sub(dozenize(s),-1,-1) == "2") then
		return "nd"
	elseif (string.sub(dozenize(s),-1,-1) == "3") then
		return "rd"
	else
		return "th"
	end
end

function is_leap_y(y)
	if ((y % 4) == 0) then
		if ((y % 100) == 0) then
			if ((y % 400) == 0) then
				return true
			else
				return false
			end
		else
			return true
		end
	else
		return false
	end
end

function easter(y)
	local a = y % 19
	local b = math.floor(y / 100)
	local c = y % 100
	local d = math.floor(b / 4)
	local e = b % 4
	local f = math.floor((b + 8) / 25)
	local g = math.floor((b - f + 1) / 3)
	local h = (19 * a + b - d - g + 15) % 30
	local i = math.floor(c / 4)
	local k = c % 4
	local L = (32 + 2 * e + 2 * i - h - k) % 7
	local m = math.floor((a + 11 * h + 22 * L) / 451)
	eastermonth = math.floor((h + L - 7 * m + 114) / 31)
	easterday = ((h + L - 7 * m + 114) % 31) + 1
--	print("Easter: "..dozenize(y).."-"..dozenize(eastermonth)..
--		"-"..dozenize(easterday))
	return y, eastermonth, easterday
end

function dow_from_jdn(jdn)
	return ((math.floor(jdn)+1) % 7)
end

function next_sunday(jdn)
	local holder = jdn
	if (dow_from_jdn(holder) == 0) then
		holder = holder + 1
	end
	while (dow_from_jdn(holder) ~= 0) do
		holder = holder + 1
	end
	return holder
end

function last_sunday(jdn)
	local holder = jdn
	if (dow_from_jdn(holder) == 0) then
		holder = holder - 1
	end
	while (dow_from_jdn(holder) ~= 0) do
		holder = holder - 1
	end
	return holder
end

function print_date(year,month,day)
	return dozenize(year).."-"..dozenize(month).."-"..dozenize(day)
end

function saints_feasts(year,returntab,index)
	table.insert(saints,{greg_to_jdn(year,1,5),"St. Telephorus, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,1,11),"St. Hyginus, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,1,14),"St. Hilary, ED",
		"III Class"})
	table.insert(saints,{greg_to_jdn(year,1,14),"St. Felix, SM",
		"Comm"})
	table.insert(saints,{greg_to_jdn(year,1,15),"St. Paul, Hermit, C",
		"III Class"})
	table.insert(saints,{greg_to_jdn(year,1,15),"St. Maurus, A",
		"Comm"})
	table.insert(saints,{greg_to_jdn(year,1,16),"St. Marcellus I, PM",
		"III Class"})
	table.insert(saints,{greg_to_jdn(year,1,17),"St. Anthony, A",
		"III Class"})
	table.insert(saints,{greg_to_jdn(year,1,18),"St. Priscilla, VM",
		"Comm"})
	table.insert(saints,{greg_to_jdn(year,1,19),
		"Sts. Marius, Martha, Audifax, and Abachum, MM", "Comm"})
	table.insert(saints,{greg_to_jdn(year,1,19),"St. Canute, M",
		"Comm"})
	table.insert(saints,{greg_to_jdn(year,1,20),
		"St. Fabian, P, and St. Sebatian, MM", "III Class"})
	table.insert(saints,{greg_to_jdn(year,1,21), "St. Agnes, VM",
		"III Class"})
	table.insert(saints,{greg_to_jdn(year,1,22), 
		"St. Vincent and Anastasius, MM", "III Class"})
	table.insert(saints,{greg_to_jdn(year,1,23), 
		"St. Raymund of Penafort, C", "III Class"})
	table.insert(saints,{greg_to_jdn(year,1,23), 
		"St. Emerentiana, VM", "Comm"})
	table.insert(saints,{greg_to_jdn(year,1,24), 
		"St. Timothy, EM", "III Class"})
	table.insert(saints,{greg_to_jdn(year,1,25), 
		"Conversion of St. Paul, Ap.", "III Class"})
	table.insert(saints,{greg_to_jdn(year,1,25), 
		"St. Peter, Ap.", "Comm"})
	table.insert(saints,{greg_to_jdn(year,1,26), 
		"St. Polycarp, EM", "III Class"})
	table.insert(saints,{greg_to_jdn(year,1,27), 
		"St. John Chrysostom, ECD", "III Class"})
	table.insert(saints,{greg_to_jdn(year,1,28), 
		"St. Peter Nolasco, C", "III Class"})
	table.insert(saints,{greg_to_jdn(year,1,28), 
		"St. Agnes, VM", "Comm"})
	table.insert(saints,{greg_to_jdn(year,1,29), 
		"St. Francis de Sales, ECD", "III Class"})
	table.insert(saints,{greg_to_jdn(year,1,30), 
		"St. Martina, VM", "III Class"})
	table.insert(saints,{greg_to_jdn(year,1,31), 
		"St. John Bosco, C", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,1), 
		"St. Ignatius, EM", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,3), 
		"St. Blase, EM", "Comm"})
	table.insert(saints,{greg_to_jdn(year,2,4), 
		"St. Andrew Corsini, EC", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,5), 
		"St. Agatha, VM", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,6), 
		"St. Titus, EC", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,6), 
		"St. Dorothy, VM", "Comm"})
	table.insert(saints,{greg_to_jdn(year,2,7), 
		"St. Romuald, A", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,8), 
		"St. John of Matha, C", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,9), 
		"St. Cyril of Alexandria, ECD", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,10), 
		"St. Scholastica, V", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,11), 
		"Apparition of the Blessed Virgin Mary Immaculate", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,12), 
		"Seven Holy Founders of the Order of Servants of the Blessed Virgin Mary, C", "III Class"})
	table.insert(saints,{greg_to_jdn(year,2,14), 
		"St. Valentine, SM","Comm"})
	table.insert(saints,{greg_to_jdn(year,2,15), 
		"Sts. Faustinus and Jovita, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,2,18), 
		"St. Simeon, EM","Comm"})
	table.insert(saints,{greg_to_jdn(year,2,23), 
		"St. Peter Damian, C","III Class"})
	if (is_leap_y(year)) then
		table.insert(saints,{greg_to_jdn(year,2,28), 
			"St. Gabriel of Our Lady of Sorrows","III Class"})
	else
		table.insert(saints,{greg_to_jdn(year,2,27), 
			"St. Gabriel of Our Lady of Sorrows","III Class"})
	end
	table.insert(saints,{greg_to_jdn(year,3,4), 
		"St. Casimir, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,4), 
		"St. Lucius I, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,3,6), 
		"Sts. Perpetua and Felicity, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,7), 
		"St. Thomas Aquinas, CD","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,8), 
		"St. John of God, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,9), 
		"St. Frances of Rome, Widow","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,10), 
		"The Forty Holy Martyrs","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,12), 
		"St. Gregory I, PCD","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,17), 
		"St. Patrick, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,18), 
		"St. Cyril of Jerusalem, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,21), 
		"St. Benedict, A","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,24), 
		"St. Gabriel the Archangel","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,27), 
		"St. John Damascene, CD","III Class"})
	table.insert(saints,{greg_to_jdn(year,3,28), 
		"St. John Capistran, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,2), 
		"St. Francis of Paula, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,4), 
		"St. Isidore, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,5), 
		"St. Vincent Ferrer, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,11), 
		"St. Leo I, PCD","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,13), 
		"St. Hermenegild, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,14), 
		"St. Justin, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,14), 
		"Sts. Tiburtius, Valerian, and Maximus, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,4,17), 
		"St. Anicetus, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,4,21), 
		"St. Anselm, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,22), 
		"Sts. Soter and Cajus, PM","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,23), 
		"St. George, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,4,24), 
		"St. Fidelis of Sigmaringen, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,26), 
		"Sts. Cletus and Marcellinus, PM","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,27), 
		"St. Peter Canisius, CD","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,28), 
		"St. Paul of the Cross, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,29), 
		"St. Peter Martyr, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,4,30), 
		"St. Catherine of Siena, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,2), 
		"St. Athanasius, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,3), 
		"Sts. Alexander, Eventius, and Theodolus, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,5,3), 
		"St. Juvenal, EC","Comm"})
	table.insert(saints,{greg_to_jdn(year,5,4), 
		"St. Monica, Widow","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,5), 
		"St. Pius V, PM","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,7), 
		"St. Stanislaus, EM","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,9), 
		"St. Gregory Nazianzen, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,10), 
		"St. Antoninus, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,10), 
		"Sts. Goridan and Epimachus","Comm"})
	table.insert(saints,{greg_to_jdn(year,5,12), 
		"Sts. Nereus, Achilleus, Domitilla, V, and Pancras, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,13), 
		"St. Robert Bellarmine, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,14), 
		"St. Boniface, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,5,15), 
		"St. John Baptist de la Salle, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,16), 
		"St. Ubald, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,17), 
		"St. Paschal Baylon, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,18), 
		"St. Venantius, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,19), 
		"St. Peter Celestine, PC","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,19), 
		"St. Pudentiana, V","Comm"})
	table.insert(saints,{greg_to_jdn(year,5,20), 
		"St. Bernardine of Siena, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,25), 
		"St. Gregory VII, PC","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,25), 
		"St. Urban I, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,5,26), 
		"St. Philip Neri, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,26), 
		"St. Eleutherius, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,5,27), 
		"St. Bede the Venerable, CD","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,27), 
		"St. John I, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,5,28), 
		"St. Augustine, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,29), 
		"St. Mary Magdalen de Pazzi, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,5,30), 
		"St. Felix I, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,5,31), 
		"St. Petronilla, V","Comm"})
	table.insert(saints,{greg_to_jdn(year,6,1), 
		"St. Angela Merici, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,2), 
		"Sts. Marcellinus, Peter, and Eramus, EM","Comm"})
	table.insert(saints,{greg_to_jdn(year,6,4), 
		"St. Francis Caracciolo, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,5), 
		"St. Boniface, EM","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,6), 
		"St. Norbert, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,9), 
		"Sts. Primus and Felician, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,6,10), 
		"St. Margaret, Queen, Widow","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,11), 
		"St. Barnabas, Ap.","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,12), 
		"St. John of San Facundo, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,12), 
		"Sts. Basilides, Cyrinus, Nabor, and Nazarius, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,6,13), 
		"St. Anthony of Padua, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,14), 
		"St. Basil the Great, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,15), 
		"Sts. Vitus, Modestus, and Crescentia, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,6,17), 
		"St. Gregory Barbarigo, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,18), 
		"St. Ephraem Syrus, De.CD","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,18), 
		"Sts. Mark and Marcellianus, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,6,19), 
		"St. Juliana Falconieri, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,19), 
		"Sts. Gervase and Protase, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,6,20), 
		"St. Silverius, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,6,21), 
		"St. Aloysius Gonzaga, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,22), 
		"St. Paulinus, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,25), 
		"St. William, A","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,29), 
		"Sts. John and Paul, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,6,30), 
		"St. Paul the Apostle","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,2), 
		"Sts. Processus and Martinian, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,3), 
		"St. Irenaeus, EM","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,5), 
		"St. Anthony Mary Zaccaria, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,7), 
		"Sts. Cyril and Methodius, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,8), 
		"St. Elizabeth, Queen, Widow","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,10), 
		"Seven Holy Brothers, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,10), 
		"Sts. Rufina and Secunda, VM","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,11), 
		"St. Pius I, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,12), 
		"St. John Gualbert, A","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,12), 
		"Sts. Nabor and Felix, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,14), 
		"St. Bonaventure, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,15), 
		"St. Henry II, Emperor, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,16), 
		"Blessed Virgin Mary of Mt. Carmel","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,17), 
		"St. Alexius, C","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,18), 
		"St. Camillus de Lellis, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,18), 
		"St. Symphorosa and her Seven Sons, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,19), 
		"St. Vincent de Paul, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,20), 
		"St. Jerome Emiliani, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,20), 
		"St. Margaret, VM","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,21), 
		"St. Lawrence of Brindisi, CD","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,21), 
		"St. Praxedes, V","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,22), 
		"St. Mary Magdalene, Penitent","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,23), 
		"St. Apollinaris, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,23), 
		"St. Liborius, EC","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,24), 
		"St. Christina, VM","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,25), 
		"St. Christopher, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,27), 
		"St. Pantaleon, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,28), 
		"Sts. Nazarius and Celsus, M; St. Victor I, PM; St.  Innocent I, PC","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,29), 
		"St. Martha, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,7,29), 
		"Sts. Felix, Simplicius, Faustinus, and Beatrice, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,30), 
		"Sts. Abdon and Sennen, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,7,31), 
		"St. Ignatius, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,1), 
		"Holy Machabees, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,2), 
		"St. Alphonsus Mary of Liguori, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,2), 
		"St. Stephen I, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,4), 
		"St. Dominic, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,5), 
		"Dedication of Our Lady of the Snows","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,6), 
		"Sts. Xystus I, P, Felicissimus, and Agapitus, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,7), 
		"St. Cajetan, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,7), 
		"St. Donatus, EM","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,8), 
		"St. John Mary Vianney, SC","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,8), 
		"Sts. Cyriacus, Largus, and Smaragdus, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,9), 
		"Vigil of St. Lawrence","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,9), 
		"St. Romanus, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,11), 
		"Sts. Tiburtius and Susanna, V, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,12), 
		"St. Clare, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,13), 
		"Sts. Hippolytus and Cassian, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,14), 
		"St. Eusebius, C","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,17), 
		"St. Hyacinth of Poland, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,18), 
		"St. Agapitus, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,19), 
		"St. John Eudes, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,20), 
		"St. Bernard, AD","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,21), 
		"St. Jane Frances de Chantal, Widow","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,22), 
		"Sts. Timothy and Companions, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,23), 
		"St. Philip Benizi, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,25), 
		"St. Louis, King, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,26), 
		"St. Zephyrinus, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,27), 
		"St. Joseph Calasanctius, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,28), 
		"St. Augustine, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,28), 
		"St. Hermes, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,29), 
		"Beheading of St. John the Baptist","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,29), 
		"St. Sabina, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,30), 
		"St. Rose of Lima, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,8,30), 
		"Sts. Felix and Adauctus, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,8,31), 
		"St. Raymond Nonnatus, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,1), 
		"St. Giles, A","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,1), 
		"Holy Twelve Brothers, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,2), 
		"St. Stephen, King, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,3), 
		"St. Pius X, PC","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,5), 
		"St. Laurence Justinian, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,8), 
		"St. Hadrian, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,9), 
		"St. Gorgonius, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,10), 
		"St. Nicholas of Tolentino, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,11), 
		"Sts. Protus and Hyacinth, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,12), 
		"Most Holy Name of Mary","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,15), 
		"St. Nicomedes, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,16), 
		"St. Cornelius, P, and St. Cyprian, E, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,16), 
		"Sts. Euphemia, V, Lucy and Geminianus, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,17), 
		"Stigmata of St. Francis, C","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,18), 
		"St. Joseph of Cupertino, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,19), 
		"St. Januarius, E, and Companions, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,20), 
		"St. Eustace and Companions, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,22), 
		"St. Thomas of Villanova, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,22), 
		"Sts. Maurice and Companions, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,23), 
		"St. Linus, PM","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,23), 
		"St. Thecla, VM","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,24), 
		"Our Lady of Ransom","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,26), 
		"Sts. Cyprian and Justina, V, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,9,27), 
		"Sts. Cosmas and Damian, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,28), 
		"St. Wenceslaus, Duke, M","III Class"})
	table.insert(saints,{greg_to_jdn(year,9,30), 
		"St. Jerome, SCD","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,1), 
		"St. Remigius, EC","Comm"})
	table.insert(saints,{greg_to_jdn(year,10,2), 
		"Holy Guardian Angels","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,3), 
		"St. Teresa of the Child Jesus, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,4), 
		"St. Francis of Assisi","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,5), 
		"St. Placid and Companions, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,10,6), 
		"St. Bruno, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,7), 
		"St. Mark, PC","Comm"})
	table.insert(saints,{greg_to_jdn(year,10,8), 
		"St. Bridget, Widow","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,8), 
		"Sts. Sergius, Bacchus, Marcellus, and Apuleius, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,10,9), 
		"St. John Leonard, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,9), 
		"Sts. Denis, E, Rusticus, S, and Elutherius, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,10,10), 
		"St. Francis Borgia, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,13), 
		"St. Edward, King, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,14), 
		"St. Callistus, PM","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,15), 
		"St. Teresa, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,16), 
		"St. Hedwig, Widow","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,17), 
		"St. Margaret Mary Alacoque, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,19), 
		"St. Peter of Alcantara, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,20), 
		"St. John Cantius, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,21), 
		"St. Hilarion, A","Comm"})
	table.insert(saints,{greg_to_jdn(year,10,21), 
		"Sts. Ursula and Companions, VM","Comm"})
	table.insert(saints,{greg_to_jdn(year,10,23), 
		"St. Anthony Mary Claret, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,24), 
		"St. Raphael Archangel","III Class"})
	table.insert(saints,{greg_to_jdn(year,10,25), 
		"Sts. Chrysanthus and Daria, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,10,26), 
		"St. Evaristus, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,11,4), 
		"St. Charles, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,4), 
		"Sts. Vitalis and Agricola, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,11,8), 
		"Holy Four Crowned Martyrs","Comm"})
	table.insert(saints,{greg_to_jdn(year,11,9), 
		"St. Theodore, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,11,10), 
		"St. Andrew Avellino, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,10), 
		"Sts. Tryphon, Respicius, and Nympha, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,11,11), 
		"St. Martin, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,11), 
		"St. Mennas, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,11,12), 
		"St. Martin I, PM","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,13), 
		"St. Didacus, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,14), 
		"St. Josaphat, EM","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,15), 
		"St. Albert the Great, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,16), 
		"St. Gertrude, V","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,17), 
		"St. Gregory Thaumaturgus, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,18), 
		"Dedication of the Basilica of Sts. Peter and Paul","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,19), 
		"St. Elisabeth, Widow","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,19), 
		"St. Pontianus, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,11,20), 
		"St. Felix of Valois, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,21), 
		"Presentation of the Blessed Virgin Mary","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,22), 
		"St. Cecilia, VM","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,23), 
		"St. Clement I, PM","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,23), 
		"St. Felicitas, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,11,24), 
		"St. John of the Cross, CD","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,24), 
		"St. Chrysogonus, M","Comm"})
	table.insert(saints,{greg_to_jdn(year,11,25), 
		"St. Catherine, VM","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,26), 
		"St. Sylvester, A","III Class"})
	table.insert(saints,{greg_to_jdn(year,11,26), 
		"St. Peter of Alexandria, EM","Comm"})
	table.insert(saints,{greg_to_jdn(year,11,29), 
		"St. Saturninus","Comm"})
	table.insert(saints,{greg_to_jdn(year,12,2), 
		"St. Bibiana, VM","III Class"})
	table.insert(saints,{greg_to_jdn(year,12,3), 
		"St. Francis Xavier, C","III Class"})
	table.insert(saints,{greg_to_jdn(year,12,4), 
		"St. Peter Chrysologus, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,12,4), 
		"St. Barbara, VM","Comm"})
	table.insert(saints,{greg_to_jdn(year,12,5), 
		"St. Sabbas, A","Comm"})
	table.insert(saints,{greg_to_jdn(year,12,6), 
		"St. Nicholas, EC","III Class"})
	table.insert(saints,{greg_to_jdn(year,12,7), 
		"St. Ambrose, ECD","III Class"})
	table.insert(saints,{greg_to_jdn(year,12,10), 
		"St. Melchiades, PM","Comm"})
	table.insert(saints,{greg_to_jdn(year,12,11), 
		"St. Damasus I, PC","III Class"})
	table.insert(saints,{greg_to_jdn(year,12,13), 
		"St. Lucy, VM","III Class"})
	table.insert(saints,{greg_to_jdn(year,12,16), 
		"St. Eusebius, EM","III Class"})
	table.insert(saints,{greg_to_jdn(year,12,21), 
		"St. Thomas, Ap.","II Class"})
	table.insert(saints,{greg_to_jdn(year,12,21), 
		"St. Thomas, Ap.","II Class"})
	table.insert(saints,{greg_to_jdn(year,12,29), 
		"St. Thomas, EM","Comm"})
	table.insert(saints,{greg_to_jdn(year,12,31), 
		"St. Sylvester I, PM","Comm"})
end

function fill_year(year,returntab,index)
	-- Easter season
	jdn_easter = greg_to_jdn(easter(year))
	table.insert(usedvals,jdn_easter)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter)),
			TITLE="Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+1)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+1)),
			TITLE="Easter Monday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+2)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+2)),
			TITLE="Easter Tuesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+3)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+3)),
			TITLE="Easter Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+4)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+4)),
			TITLE="Easter Thursday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+5)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+5)),
			TITLE="Easter Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+6)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+6)),
			TITLE="Easter Saturday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-2)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-2)),
			TITLE="Good Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-3)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-3)),
			TITLE="Holy Thursday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-4)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-4)),
			TITLE="Spy Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-5)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-5)),
			TITLE="Tuesday in Holy Week",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-6)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-6)),
			TITLE="Monday in Holy Week",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-46)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-46)),
			TITLE="Ash Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	ash_wednes = jdn_easter-46
	table.insert(usedvals,jdn_easter-7)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-7)),
			TITLE="Palm Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	palm_sunday = jdn_easter-7
	table.insert(usedvals,jdn_easter-14)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-14)),
			TITLE="Passion Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-9)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-9)),
			TITLE="Seven Sorrows of the Blessed Virgin Mary",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="Comm,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-21)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-21)),
			TITLE="4th Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-28)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-28)),
			TITLE="3rd Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-35)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-35)),
			TITLE="2nd Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-42)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-42)),
			TITLE="1st Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-39)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-39)),
			TITLE="Ember Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="II Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-37)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-37)),
			TITLE="Ember Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="II Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-36)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-36)),
			TITLE="Ember Saturday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="II Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-49)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-49)),
			TITLE="Quinquegesima",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-56)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-56)),
			TITLE="Sexagesima",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-63)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-63)),
			TITLE="Septuagesima",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	jdn_septua = jdn_easter-63
	-- Christmas season
	jdn_epiph = greg_to_jdn(year,1,6)
	table.insert(usedvals,jdn_epiph)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_epiph)),
			TITLE="Epiphany",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,christmas"
	}
	index = index + 1
	table.insert(usedvals,jdn_epiph-5)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_epiph-5)),
			TITLE="Circumcision of Our Lord",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,christmas"
	}
	circumcision = jdn_epiph-5
	index = index + 1
	table.insert(usedvals,next_sunday(jdn_epiph))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(next_sunday(jdn_epiph))),
			TITLE="Holy Family",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,christmas"
	}
	index = index + 1
	jdn_holyfamily = next_sunday(jdn_epiph)
	modif = 7
	afterepiph = 2
	while (jdn_holyfamily+modif < jdn_septua) do
		table.insert(usedvals,jdn_holyfamily+modif)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(jdn_holyfamily+modif)),
				TITLE=afterepiph..last_char(afterepiph)..
					" Sunday after Epiphany",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,christmas"
		}
		index = index + 1
		modif = modif + 7
		afterepiph = afterepiph + 1
	end
	local holder = jdn_epiph;
	--[[ Holy Name:  Sunday between Circ. and Epiph. if there
	is one, Jan 2 if not ]]--
	while ((dow_from_jdn(holder) ~= 0) and (holder ~= (jdn_epiph - 5))) do
		holder = holder - 1;
	end
	if (holder == (jdn_epiph - 5)) then
		table.insert(usedvals,greg_to_jdn(year,1,2))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,1,2))),
				TITLE="Most Holy Name of Jesus",CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,christmas"
		}
	else
		table.insert(usedvals,next_sunday(jdn_epiph-5))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(next_sunday(jdn_epiph-5))),
				TITLE="Most Holy Name of Jesus",CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,christmas"
		}
	end
	index = index + 1
	-- end of year Christmas season
	jdn_christmas = greg_to_jdn(year,12,25)
	table.insert(usedvals,jdn_christmas)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_christmas)),
			TITLE="Christmas",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,christmas"
	}
	index = index + 1
	table.insert(usedvals,jdn_christmas-1)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_christmas-1)),
			TITLE="Vigil of Christmas",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,christmas"
	}
	index = index + 1
	christmas_holder = greg_to_jdn(year,12,29)
	while (christmas_holder < greg_to_jdn(year+1,1,1)) do
		if (dow_from_jdn(christmas_holder) ~= 0) then
			table.insert(usedvals,christmas_holder)
			returntab[index] = {
				START_DATE=print_date(jdn_to_greg(christmas_holder)),
					TITLE="Feria",CLASS="Catholic:  1176",
					START_TIME="",END_TIME="", LOCATION="",
					CATEGORY="II Class,traditional,catholic,christmas"
			}
			index = index + 1
		end
		christmas_holder = christmas_holder + 1
	end
	-- Advent season
	table.insert(usedvals,last_sunday(jdn_christmas))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas))),
			TITLE="4th Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,advent"
	}
	index = index + 1
	table.insert(usedvals,last_sunday(jdn_christmas)-7)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas)-7)),
			TITLE="3rd Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,advent"
	}
	third_sun_adv = (last_sunday(jdn_christmas))-7
	index = index + 1
	table.insert(usedvals,third_sun_adv+3)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(third_sun_adv+3)),
			TITLE="Ember Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,advent"
	}
	index = index + 1
	table.insert(usedvals,third_sun_adv+5)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(third_sun_adv+5)),
			TITLE="Ember Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,advent"
	}
	index = index + 1
	table.insert(usedvals,third_sun_adv+6)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(third_sun_adv+6)),
			TITLE="Ember Saturday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,advent"
	}
	index = index + 1
	if ((last_sunday(jdn_christmas)-14) == greg_to_jdn(year,12,8)) then
		secadvcat = "Comm"
	else
		secadvcat = "I Class"
	end
	table.insert(usedvals,last_sunday(jdn_christmas)-14)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas)-14)),
			TITLE="2nd Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY=secadvcat..",traditional,catholic,advent"
	}
	index = index + 1
	table.insert(usedvals,last_sunday(jdn_christmas)-21)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas)-21)),
			TITLE="1st Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,advent"
	}
	index = index + 1
	first_sun_adv = last_sunday(jdn_christmas)-21
	-- Easter Season
	table.insert(usedvals,jdn_easter+7)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+7)),
			TITLE="Low Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+14)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+14)),
			TITLE="2nd Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+21)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+21)),
			TITLE="3rd Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+28)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+28)),
			TITLE="4th Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+35)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+35)),
			TITLE="5th Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+38)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+38)),
			TITLE="Vigil of the Ascension",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+39)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+39)),
			TITLE="Ascension Thursday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+42)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+42)),
			TITLE="6th Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+49)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+49)),
			TITLE="Pentecost",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	jdn_pente = jdn_easter+49
	table.insert(usedvals,jdn_easter+50)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+50)),
			TITLE="Monday in the Octave of Pentecost",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+51)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+51)),
			TITLE="Tuesday in the Octave of Pentecost",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+52)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+52)),
			TITLE="Ember Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+53)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+53)),
			TITLE="Thursday in the Octave of Pentecost",
			CLASS="Catholic:  1176", START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+54)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+54)),
			TITLE="Ember Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+55)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+55)),
			TITLE="Ember Saturday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+56)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+56)),
			TITLE="Trinity Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,pentecost"
	}
	index = index + 1
	-- Make sure Pentecost doesn't overwrite Christ the King
	jdn_ctk = last_sunday(greg_to_jdn(year,11,1))
	modif = 7
	afterpent = 1
	while (jdn_pente+modif < jdn_ctk) do
		table.insert(usedvals,jdn_pente+modif)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(jdn_pente+modif)),
				TITLE=dozenize(afterpent)..last_char(afterpent)..
					" Sunday after Pentecost",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
		afterpent = afterpent + 1
		modif = modif + 7
	end
	table.insert(usedvals,jdn_ctk)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_ctk)),
			TITLE="Christ the King",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	modif = modif + 7
	afterpent = afterpent + 1
	jdn_first_sunday_advent = last_sunday(jdn_christmas)-21
	while (jdn_pente+modif < jdn_first_sunday_advent) do
		table.insert(usedvals,jdn_pente+modif)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(jdn_pente+modif)),
				TITLE=dozenize(afterpent)..last_char(afterpent)..
					" Sunday after Pentecost",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
		afterpent = afterpent + 1
		modif = modif + 7
	end
	modif = 8
	while ((jdn_christmas-modif < jdn_christmas)) do
		if (dow_from_jdn(jdn_christmas-modif) ~= 0) then
			table.insert(usedvals,jdn_christmas-modif)
			returntab[index] = {
				START_DATE=print_date(jdn_to_greg(jdn_christmas-modif)),
					TITLE="Feria",
					CLASS="Catholic:  1176",
					START_TIME="",END_TIME="", LOCATION="",
					CATEGORY="II Class,traditional,catholic,feast"
			}
			index = index + 1
		end
		modif = modif - 1
	end
	table.insert(usedvals,jdn_christmas+1)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_christmas+1)),
			TITLE="St. Stephen the Protomartyr, M",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	table.insert(usedvals,jdn_christmas+2)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_christmas+2)),
			TITLE="St. John the Evangelist, Ap",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	table.insert(usedvals,jdn_christmas+3)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_christmas+3)),
			TITLE="Holy Innocents, M",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	if ((next_sunday(jdn_christmas) < greg_to_jdn(year+1,1,1))
	and (donedate(next_sunday(jdn_christmas)) == false)) then
		table.insert(usedvals,jdn_christmas)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(next_sunday(jdn_christmas))),
				TITLE="Sunday within the Octave of Christmas",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="traditional,catholic,christmas"
		}
		index = index + 1
	end
	modif = 0
	while ((jdn_christmas+modif < greg_to_jdn(year+1,1,1))) do
		if (donedate(jdn_christmas+modif) == false) then
			table.insert(usedvals,jdn_christmas+modif)
			returntab[index] = {
				START_DATE=print_date(jdn_to_greg(jdn_christmas+modif)),
					TITLE="Feria",
					CLASS="Catholic:  1176",
					START_TIME="",END_TIME="", LOCATION="",
					CATEGORY="II Class,traditional,catholic,feast"
			}
			index = index + 1
		end
		modif = modif + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,11,2)) == 0) then
		allsouls = greg_to_jdn(year,11,3);
	elseif (dow_from_jdn(greg_to_jdn(year,11,2)) == 1) then
		allsouls = greg_to_jdn(year,11,4);
	else
		allsouls = greg_to_jdn(year,11,2);
	end
	table.insert(usedvals,allsouls)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(allsouls)),
			TITLE="All Souls' Day",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	table.insert(usedvals,allsouls-1)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(allsouls-1)),
			TITLE="All Saints' Day",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	table.insert(usedvals,greg_to_jdn(year,2,22))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,2,22))),
			TITLE="Chair of St. Peter",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	holycross = greg_to_jdn(year,9,14)
	table.insert(usedvals,greg_to_jdn(year,9,14))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,9,14))),
			TITLE="Exaltation of the Holy Cross",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	table.insert(usedvals,greg_to_jdn(year,1,13))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,1,13))),
			TITLE="Baptism of the Lord",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	joseph_spouse = move_from_sun(greg_to_jdn(year,3,19))
	table.insert(usedvals,joseph_spouse)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(joseph_spouse)),
			TITLE="St. Joseph, Spouse of the Blessed Virgin Mary, C, and Patron of the Universal Church",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	annunciation = move_from_sun(greg_to_jdn(year,3,25))
	table.insert(usedvals,annunciation)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(annunciation)),
			TITLE="Annunciation of the Blessed Virgin Mary",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	joseph_worker = move_from_sun(greg_to_jdn(year,5,1))
	table.insert(usedvals,joseph_worker)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(joseph_worker)),
			TITLE="St. Joseph the Workman, Spouse of the Blessed Virgin Mary",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	nativity_john = move_from_sun(greg_to_jdn(year,6,24))
	table.insert(usedvals,nativity_john)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(nativity_john)),
			TITLE="Nativity of St. John the Baptist",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	if (dow_from_jdn(nativity_john-1) ~= 0) then
		table.insert(usedvals,nativity_john-1)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(nativity_john-1)),
				TITLE="Vigil of the Nativity of St. John the Baptist",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	peter_and_paul = move_from_sun(greg_to_jdn(year,6,29))
	table.insert(usedvals,peter_and_paul)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(peter_and_paul)),
			TITLE="Sts. Peter and Paul, Ap.",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	if (dow_from_jdn(peter_and_paul-1) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,6,28))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,6,28))),
				TITLE="Vigil of Sts. Peter and Paul, Ap.",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	table.insert(usedvals,greg_to_jdn(year,7,1))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,7,1))),
			TITLE="The Most Precious Blood of Our Lord Jesus Christ",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	assumption = move_from_sun(greg_to_jdn(year,8,15))
	table.insert(usedvals,assumption)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(assumption)),
			TITLE="Assumption of the Blessed Virgin Mary",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	if (dow_from_jdn(assumption-1) ~= 0) then
		table.insert(usedvals,assumption-1)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(assumption-1)),
				TITLE="Vigil of the Assumption of the Blessed Virgin Mary",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	dedic_michael = move_from_sun(greg_to_jdn(year,9,29))
	table.insert(usedvals,dedic_michael)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(dedic_michael)),
			TITLE="Dedication of St. Michael Archangel",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	-- Delete anything from Dec 8, including Sun., then add Imm. Conc.
	ifinret(print_date(jdn_to_greg(greg_to_jdn(year,12,8))));
	table.insert(usedvals,greg_to_jdn(year,12,8))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,12,8))),
			TITLE="Immaculate Conception of the Blessed Virgin Mary",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	ifinret(print_date(jdn_to_greg(greg_to_jdn(year,2,2))));
	table.insert(usedvals,greg_to_jdn(year,2,2))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,2,2))),
			TITLE="Purification of the Blessed Virgin Mary",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	ifinret(print_date(jdn_to_greg(greg_to_jdn(year,8,6))));
	table.insert(usedvals,greg_to_jdn(year,8,6))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,8,6))),
			TITLE="Transfiguration of Our Lord Jesus Christ",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	ifinret(print_date(jdn_to_greg(greg_to_jdn(year,11,9))));
	table.insert(usedvals,greg_to_jdn(year,11,9))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,11,9))),
			TITLE="Dedication of the Archbasilica of the Most Holy Savior",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	september = next_sunday(holycross)
	table.insert(usedvals,september+3)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(september+3)),
			TITLE="Ember Wednesday",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	table.insert(usedvals,september+5)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(september+5)),
			TITLE="Ember Friday",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	table.insert(usedvals,september+6)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(september+6)),
			TITLE="Ember Saturday",
			CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	if (is_leap_y(year) == true) then
		stmatthias = greg_to_jdn(year,2,25)
	else
		stmatthias = greg_to_jdn(year,2,24)
	end
	if (dow_from_jdn(stmatthias) ~= 0) then
		table.insert(usedvals,stmatthias)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(stmatthias)),
				TITLE="St. Matthias, Ap.",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,4,25)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,4,25))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,4,25))),
				TITLE="St. Mark the Evangelist",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,5,11)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,5,11))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,5,11))),
				TITLE="Sts. Philip and James, Ap.",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,7,2)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,7,2))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,7,2))),
				TITLE="Visitation of the Blessed Virgin Mary",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,7,25)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,7,25))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,7,25))),
				TITLE="St. James, Ap.",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,7,26)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,7,26))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,7,26))),
				TITLE="St. Anne, Mother of the Blessed Virgin Mary",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,5,31)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,5,31))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,5,31))),
				TITLE="Blessed Virgin Mary, Queen",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,8,10)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,8,10))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,8,10))),
				TITLE="St. Lawrence, M",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,8,16)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,8,16))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,8,16))),
				TITLE="St. Joachim, Father of the Blessed Virgin Mary, C",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,8,22)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,8,22))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,8,22))),
				TITLE="Immaculate Heart of the Blessed Virgin Mary",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,8,24)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,8,24))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,8,24))),
				TITLE="St. Bartholomew, Ap.",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,9,8)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,9,8))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,9,8))),
				TITLE="Nativity of the Blessed Virgin Mary",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,9,15)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,9,15))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,9,15))),
				TITLE="Seven Sorrows of the Blessed Virgin Mary",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,9,21)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,9,21))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,9,21))),
				TITLE="St. Matthew, Ap. and Evangelist",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,10,7)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,10,7))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,10,7))),
				TITLE="Blessed Virgin Mary of the Rosary",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,10,11)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,10,11))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,10,11))),
				TITLE="Maternity of the Blessed Virgin Mary",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,10,18)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,10,18))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,10,18))),
				TITLE="St. Luke, Evangelist",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,10,28)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,10,28))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,10,28))),
				TITLE="Sts. Simon and Jude, Ap.",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	if (dow_from_jdn(greg_to_jdn(year,11,30)) ~= 0) then
		table.insert(usedvals,greg_to_jdn(year,11,30))
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,11,30))),
				TITLE="St. Andrew, Ap.",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
	end
	-- Ferias in Lent take precedence over saints III Class
	firstjdn = ash_wednes
	lastjdn = palm_sunday
	while (firstjdn < lastjdn) do
		if (donedate(firstjdn) == false) then
			table.insert(usedvals,firstjdn)
			returntab[index] = {
				START_DATE=print_date(jdn_to_greg(firstjdn)),
					TITLE="Feria",
					CLASS="Catholic:  1176",
					START_TIME="",END_TIME="", LOCATION="",
					CATEGORY="III Class,traditional,catholic,feast"
			}
			index = index + 1
		end
		firstjdn = firstjdn + 1
	end
	-- Do the saints feasts
	saints_feasts(year,returntab,index)
	for key,val in pairs(saints) do
		done = false
		feastclass = ""
		feastname = ""
		feast_jdn = ""
		for keytwo,value in pairs(val) do
			if (keytwo == 1) then
				feast_jdn = value
			elseif (keytwo == 2) then
				feastname = value
			elseif (keytwo == 3) then
				if (donedate(feast_jdn) == true) then
					feastclass = "Comm"
				else
					feastclass = value
				end
			end
		end
		if (feast_jdn ~= "") then
			table.insert(usedvals,feast_jdn)
			returntab[index] = {
				START_DATE=print_date(jdn_to_greg(feast_jdn)),
					TITLE=feastname,
					CLASS="Catholic:  1176",
					START_TIME="",END_TIME="", LOCATION="",
					CATEGORY=feastclass..",traditional,catholic,feast"
			}
			index = index + 1
		end
	end
	firstjdn = first_sun_adv
	lastjdn = greg_to_jdn(year,12,16)
	while (firstjdn <= lastjdn) do
		if (donedate(firstjdn) == false) then
			table.insert(usedvals,firstjdn)
			returntab[index] = {
				START_DATE=print_date(jdn_to_greg(firstjdn)),
					TITLE="Feria",
					CLASS="Catholic:  1176",
					START_TIME="",END_TIME="", LOCATION="",
					CATEGORY="III Class,traditional,catholic,feast"
			}
			index = index + 1
		end
		firstjdn = firstjdn + 1
	end
	firstjdn = greg_to_jdn(year,1,1)
	lastjdn = greg_to_jdn(year,12,31)
	while (firstjdn <= lastjdn) do
		if (donedate(firstjdn) == false) then
			table.insert(usedvals,firstjdn)
			returntab[index] = {
				START_DATE=print_date(jdn_to_greg(firstjdn)),
					TITLE="Feria",
					CLASS="Catholic:  1176",
					START_TIME="",END_TIME="", LOCATION="",
					CATEGORY="IV Class,traditional,catholic,feast"
			}
			index = index + 1
		end
		firstjdn = firstjdn + 1
	end
	return index
end

saints = {{}}
usedvals = {}
returntab = {{}}
index = 1

function dozcal_return_ev()
	return unpack(returntab)
end

function dozcal_return_ev_num()
	return fill_year(2016,returntab,index)
end
