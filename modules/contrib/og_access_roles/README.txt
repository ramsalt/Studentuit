$Id: README.txt,v 1.1.2.1 2010/01/18 01:19:05 marcp Exp $

README.txt for OG Access Roles
==============================

This module extends the reach of Organic Groups' bundled 'Organic groups
access control' module by allowing node authors finer control over who can
see their posts.

'Organic groups access control' gives node authors the option of making
their posts Public, meaning anyone can view the node, even anonymous users;
or Private, meaning only group members can view the node.

For Private posts, OG Access Roles gives node authors the ability to let
users in selected roles view nodes even if those users are not in the group
(or groups) where the node is posted.

One important use case for this module is to allow all authenticated users
to see certain private group posts.  In order to do this, simply enable the
'authenticated user' role at admin/og/og_access_roles.

OG Access Roles was developed by the friendly primates at FunnyMonkey in
response to the discussion at http://drupal.org/node/660610 in the Organic
Groups issue queue.  Amitaibu's guidance on this project was invaluable.
