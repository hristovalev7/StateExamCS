schools = [("MG", 2, (\(x,y) -> 3 * x + y)), ("LS", 1, (\(x,y) -> 4 * y + x))]
candidates = [(["MG", "LS"], (90, 30)), (["LS"], (60, 85)), (["LS", "MG"], (60, 75))]

getSchool name = head [ school | school@(n,_,_) <- schools, n == name]

assuredAdmission (_, cG) sname = length (filter (\(cSchools, cGrades) -> elem sname cSchools && gradeFunc cGrades >= gradeFunc cG) candidates)
                                  <= open
                                where (_, open, gradeFunc) = getSchool sname
                                
firstAssured = map (\candidate@(cSchools,_) -> head ((filter (\sname -> assuredAdmission candidate sname) cSchools) ++ [""])) candidates
