/*
   Copyright (C) 2023 European Space Agency - <maxime.perrotin@esa.int>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this program. If not, see <https://www.gnu.org/licenses/lgpl-2.1.html>.
*/

#include "requirement.h"

namespace requirement {

bool Requirement::isValid() const
{
    return !m_id.isEmpty() && !m_longName.isEmpty();
}

bool Requirement::operator==(const Requirement &req) const
{
    return (req.m_id == this->m_id);
}

} // namespace requirement

QDebug operator<<(QDebug debug, const requirement::Requirement &r)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "Requirement(" << r.m_id << ", " << r.m_longName << ", issue:" << r.m_issueID << ")";
    return debug;
}
