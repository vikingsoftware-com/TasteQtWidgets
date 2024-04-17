/*
   Copyright (C) 2024 European Space Agency - <maxime.perrotin@esa.int>

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

#include "gitlabreviews.h"

#include <issue.h>

using namespace gitlab;

namespace reviews {

/*!
 * Converts the given list of Gitlab issues to a list Review and sends a siganl with those
 * @param issues the list of Gitlab issues to convert
 */
QList<Review> GitLabReviews::convertIssues(const QList<gitlab::Issue> &issues)
{
    QList<Review> reviews;
    reviews.reserve(issues.size());
    for (const auto &issue : issues) {
        reviews.append(reviewFromIssue(issue));
    }
    Q_EMIT listOfReviews(reviews);
    return reviews;
}

/*!
 * Converts a Gitlab issues to a Review
 * \param issue the Gitlab issue to convert
 */
Review GitLabReviews::reviewFromIssue(const gitlab::Issue &issue)
{
    QStringList tags = issue.mLabels;
    tags.removeAll(k_reviewsTypeLabel);
    return Review { parseRevIfId(issue), issue.mTitle, issue.mDescription, issue.mAuthor, issue.mIssueIID, tags,
        issue.mUrl };
}

QString GitLabReviews::parseRevIfId(const gitlab::Issue &issue)
{
    static const QString keyWord("#revid");
    for (const QString &line : issue.mDescription.split("\n")) {
        QString id = line.trimmed();
        if (id.trimmed().startsWith(keyWord)) {
            id = id.sliced(keyWord.length());
            id = id.trimmed();
            if (id.startsWith(":")) {
                id = id.sliced(1).trimmed();
            }

            // Remove quotes if there
            if (id.startsWith("\"")) {
                id = id.sliced(1);
            }
            if (id.endsWith("\"")) {
                id.chop(1);
            }
            return id;
        }
    }
    return QString::number(issue.mIssueIID);
}

/*!
 * Returns the tags from the list of labels provided by the gitlab server
 */
QStringList GitLabReviews::tagsFromLabels(const QList<gitlab::Label> &labels)
{
    QStringList tags;
    for (const gitlab::Label &label : labels) {
        if (label.mName.compare(k_reviewsTypeLabel) != 0) {
            tags.append(label.mName);
        }
    }
    tags.removeDuplicates();
    return tags;
}
}
