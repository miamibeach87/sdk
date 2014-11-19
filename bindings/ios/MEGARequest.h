//
//  MEGARequest.h
//
//  Created by Javier Navarro on 01/10/14.
//  Copyright (c) 2014 MEGA. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MEGANode.h"
#import "MEGAAccountDetails.h"
#import "MEGAPricing.h"

typedef NS_ENUM (NSInteger, MEGARequestType) {
    MEGARequestTypeLogin,
    MEGARequestTypeCreateFolder,
    MEGARequestTypeMove,
    MEGARequestTypeCopy,
    MEGARequestTypeRename,
    MEGARequestTypeRemove,
    MEGARequestTypeShare,
    MEGARequestTypeImportLink,
    MEGARequestTypeExport,
    MEGARequestTypeFetchNodes,
    MEGARequestTypeAccountDetails,
    MEGARequestTypeChangePassword,
    MEGARequestTypeUpload,
    MEGARequestTypeLogout,
    MEGARequestTypeGetPublicNode,
    MEGARequestTypeGetAttrFile,
    MEGARequestTypeSetAttrFile,
    MEGARequestTypeGetAttrUser,
    MEGARequestTypeSetAttrUser,
    MEGARequestTypeRetryPendingConnections,
    MEGARequestTypeAddContact,
    MEGARequestTypeRemoveContact,
    MEGARequestTypeCreateAccount,
    MEGARequestTypeConfirmAccount,
    MEGARequestTypeQuerySignUpLink,
    MEGARequestTypeAddSync,
    MEGARequestTypeRemoveSync,
    MEGARequestTypeRemoveSyncs,
    MEGARequestTypePauseTransfers,
    MEGARequestTypeCancelTransfer,
    MEGARequestTypeCancelTransfers,
    MEGARequestTypeDelete,
    MEGARequestTypeReportEvent,
    MEGARequestTypeCancelAttrFile,
    MEGARequestTypeGetPricing,
    MEGARequestTypeGetPaymentURL
};

typedef NS_ENUM (NSInteger, MEGANodeAccessLevel) {
    MEGANodeAccessLevelAccessUnknown = -1,
    MEGANodeAccessLevelRdOnly = 0,            // cannot add, rename or delete
    MEGANodeAccessLevelRdWr,                  // cannot rename or delete
    MEGANodeAccessLevelFull,                  // all operations that do not require ownership permitted
    MEGANodeAccessLevelOwner,                 // node is in caller's ROOT, INCOMING or RUBBISH trees
    MEGANodeAccessLevelOwnerPreLogin
};

/**
 * @brief Provides information about an asynchronous request
 *
 * Most functions in this API are asynchonous, except the ones that never require to
 * contact MEGA servers. Developers can use delegates (MEGADelegate, MEGARequestDelegate)
 * to track the progress of each request. MEGARequest objects are provided in callbacks sent
 * to these delegates and allow developers to know the state of the request, their parameters
 * and their results.
 *
 * Objects of this class aren't live, they are snapshots of the state of the request
 * when the object is created, they are immutable.
 *
 * These objects have a high number of 'properties', but only some of them return valid values
 * for each type of request. Documentation of each request specify which fields are valid.
 *
 */
@interface MEGARequest : NSObject

/**
 * @brief The type of request associated with the object
 */
@property (readonly, nonatomic) MEGARequestType type;

/**
 * @brief A readable string that shows the type of request
 *
 * This property is a pointer to a statically allocated buffer.
 * You don't have to free the returned pointer
 *
 */
@property (readonly, nonatomic) NSString *requestString;

/**
 * @brief The handle of a node related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk moveNode:newParent:] - Returns the handle of the node to move
 * - [MEGASdk copyNode:newParent:] - Returns the handle of the node to copy
 * - [MEGASdk renameNode:newName:] - Returns the handle of the node to rename
 * - [MEGASdk removeNode:] - Returns the handle of the node to remove
 * - [MEGASdk shareNode:withUser:level:] - Returns the handle of the folder to share
 * - [MEGASdk getThumbnailWithNode:destinationFilePath:] - Returns the handle of the node to get the thumbnail
 * - [MEGASdk getPreviewlWithNode:destinationFilePath:] - Return the handle of the node to get the preview
 * - [MEGASdk setThumbnailWithNode:sourceFilePath:] - Returns the handle of the node
 * - [MEGASdk setPreviewWithNode:sourceFilePath:] - Returns the handle of the node
 * - [MEGASdk exportNode:] - Returns the handle of the node
 * - [MEGASdk disableExportNode:] - Returns the handle of the node
 * - [MEGASdk exportNode:] - Returns the handle of the product
 * - [MEGASdk getPaymentURLWithProductHandle:] - Returns the handle of the folder in MEGA
 *
 * This value is valid for these requests in onRequestFinish when the
 * error code is MEGAErrorTypeApiOk:
 * - [MEGASdk createFolderWithName:parent:] - Returns the handle of the new folder
 * - [MEGASdk copyNode:newParent:] - Returns the handle of the new node
 * - [MEGASdk importMegaFileLink:parent:] - Returns the handle of the new node
 *
 */
@property (readonly, nonatomic) uint64_t nodeHandle;

/**
 * @brief A link related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk querySignUpWithLink:] - Returns the confirmation link
 * - [MEGASdk confirmAccountWithLink:password:] - Returns the confirmation link
 * - [MEGASdk fastConfirmAccountWithLink:base64pwkey:] - Returns the confirmation link
 * - [MEGASdk loginWithFolderLink:] - Returns the link to the folder
 * - [MEGASdk importMegaFileLink:parent:] - Returns the link to the file to import
 * - [MEGASdk publicNodeWithMegaFileLink:] - Returns the link to the file
 *
 * This value is valid for these requests in onRequestFinish when the
 * error code is MEGAErrorTypeApiOk:
 * - [MEGASdk exportNode:] - Returns the public link
 * - [MEGASdk getPaymentURLWithProductHandle:] - Returns the payment link
 *
 * The SDK retains the ownership of the returned value. It will be valid until
 * the MEGARequest object is deleted.
 *
 */
@property (readonly, nonatomic) NSString *link;

/**
 * @brief The handle of a parent node related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk createFolderWithName:parent:] - Returns the handle of the parent folder
 * - [MEGASdk moveNode:newParent:] - Returns the handle of the new parent for the node
 * - [MEGASdk copyNode:newParent:] - Returns the handle of the parent for the new node
 * - [MEGASdk importMegaFileLink:parent:] - Returns the handle of the node that receives the imported file
 *
 */
@property (readonly, nonatomic) uint64_t parentHandle;

/**
 * @brief A session key related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk fastLoginWithSession:] - Returns session key used to access the account
 *
 * The SDK retains the ownership of the returned value. It will be valid until
 * the MEGARequest object is deleted.
 *
 */
@property (readonly, nonatomic) NSString *sessionKey;

/**
 * @brief A name related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk createAccountWithEmail:password:name:] - Returns the name of the user
 * - [MEGASdk fastCreateAccountWithEmail:password:name:] - Returns the name of the user
 * - [MEGASdk createFolderWithName:parent:] - Returns the name of the new folder
 * - [MEGASdk renameNode:newName:] - Returns the new name for the node
 *
 * This value is valid for these request in onRequestFinish when the
 * error code es MegaError::API_OK:
 * - [MEGASdk querySignUpWithLink:] - Returns the name of the user
 * - [MEGASdk confirmAccountWithLink:password:] - Returns the name of the user
 * - [MEGASdk fastConfirmAccountWithLink:base64pwkey:] - Returns the name of the user
 *
 * The SDK retains the ownership of the returned value. It will be valid until
 * the MEGARequest object is deleted.
 *
 */
@property (readonly, nonatomic) NSString *name;

/**
 * @brief An email related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk loginWithEmail:password:] - Returns the email of the account
 * - [MEGASdk fastLoginWithEmail:password:] - Returns the email of the account
 * - [MEGASdk loginWithFolderLink:] - Returns the string "FOLDER"
 * - [MEGASdk createAccountWithEmail:password:name:] - Returns the name of the user
 * - [MEGASdk fastCreateAccountWithEmail:password:name] - Returns the name of the user
 * - [MEGASdk shareNode:withUser:level:] - Returns the handle of the folder to share
 * - [MEGASdk getAvatarWithUser:destinationFilePath:] - Returns the email of the user to get the avatar
 * - [MEGASdk addContactWithEmail:] - Returns the email of the contact
 * - [MEGASdk removeContactWithEmail:] - Returns the email of the contact
 *
 * This value is valid for these request in onRequestFinish when the
 * error code es MegaError::API_OK:
 * - [MEGASdk querySignUpWithLink:] - Returns the name of the user
 * - [MEGASdk confirmAccountWithLink:password:] - Returns the name of the user
 * - [MEGASdk fastConfirmAccountWithLink:base64pwkey:] - Returns the name of the user
 *
 * The SDK retains the ownership of the returned value. It will be valid until
 * the MEGARequest object is deleted.
 *
 */
@property (readonly, nonatomic) NSString *email;

/**
 * @brief A password related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk loginWithEmail:password:] - Returns the email of the account
 * - [MEGASdk fastLoginWithEmail:password:] - Returns the email of the account
 * - [MEGASdk createAccountWithEmail:password:name:] - Returns the name of the user
 * - [MEGASdk confirmAccountWithLink:password:] - Returns the password for the account
 * - [MEGASdk changePasswordWithOldPassword:newPassword:]  - Returns the old password of the account (first parameter)
 *
 * The SDK retains the ownership of the returned value. It will be valid until
 * the MEGARequest object is deleted.
 *
 */
@property (readonly, nonatomic) NSString *password;

/**
 * @brief A new password related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk changePasswordWithOldPassword:newPassword:]  - Returns the old password of the account (first parameter)
 *
 * The SDK retains the ownership of the returned value. It will be valid until
 * the MEGARequest object is deleted.
 *
 */
@property (readonly, nonatomic) NSString *newPassword;

/**
 * @brief Returns a private key related to the request
 *
 * The SDK retains the ownership of the returned value. It will be valid until
 * the MEGARequest object is deleted.
 *
 * This value is valid for these requests:
 * - [MEGASdk fastLoginWithEmail:password:] - Returns the base64pwKey parameter
 * - [MEGASdk fastCreateAccountWithEmail:password:name] - Returns the base64pwKey parameter
 * - [MEGASdk fastConfirmAccountWithLink:base64pwkey:] - Returns the base64pwKey parameter
 *
 */
@property (readonly, nonatomic) NSString *privateKey;

/**
 * @brief An access level related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk shareNode:withUser:level:] - Returns the access level for the shared folder
 * - [MEGASdk exportNode:] - Returns YES
 * - [MEGASdk disableExportNode:] - Returns false
 *
 */
@property (readonly, nonatomic) MEGANodeAccessLevel accessLevel;

/**
 * @brief The path of a file related to the request
 *
 * The SDK retains the ownership of the returned value. It will be valid until
 * the MEGARequest object is deleted.
 *
 * This value is valid for these requests:
 * - [MEGASdk getThumbnailWithNode:destinationFilePath:] - Returns the destination path for the thumbnail
 * - [MEGASdk getPreviewlWithNode:destinationFilePath:] - Returns the destination path for the preview
 * - [MEGASdk getAvatarWithUser:destinationFilePath:] - Returns the destination path for the avatar
 * - [MEGASdk setThumbnailWithNode:sourceFilePath:] - Returns the source path for the thumbnail
 * - [MEGASdk setPreviewWithNode:sourceFilePath:] - Returns the source path for the preview
 *
 */
@property (readonly, nonatomic) NSString *file;

/**
 * @brief A public node related to the request
 *
 * The MEGARequest object retains the ownership of the returned value. It will be valid
 * until the MEGARequest object is deleted.
 *
 * If you want to use the returned node beyond the deletion of the MegaRequest object,
 * you must call [MEGANode clone] or use [MEGARequest publicNode] instead
 *
 * @return Public node related to the request
 *
 * @deprecated This function will be removed in future updates. You should use
 * MegaRequest::getPublicMegaNode instead.
 *
 */
@property (readonly, nonatomic) MEGANode *publicNode;

/**
 * @brief The type of parameter related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk getThumbnailWithNode:destinationFilePath:] - Returns MegaApi::ATTR_TYPE_THUMBNAIL
 * - [MEGASdk getPreviewlWithNode:destinationFilePath:] - Returns MegaApi::ATTR_TYPE_PREVIEW
 * - [MEGASdk setThumbnailWithNode:sourceFilePath:] - Returns MegaApi::ATTR_TYPE_THUMBNAIL
 * - [MEGASdk setPreviewWithNode:sourceFilePath:] - Returns MegaApi::ATTR_TYPE_PREVIEW
 *
 */
@property (readonly, nonatomic) NSInteger paramType;

/**
 * @brief A flag related to the request
 *
 * This value is valid for these requests:
 * - [MEGASdk retryPendingConnections:] - Returns if request are disconnected
 *
 */
@property (readonly, nonatomic) BOOL flag;

/**
 * @brief The number of transferred bytes during the request
 */
@property (readonly, nonatomic) NSNumber *transferredBytes;

/**
 * @brief The number of bytes that the SDK will have to transfer to finish the request
 */
@property (readonly, nonatomic) NSNumber *totalBytes;

/**
 * @brief Details related to the MEGA account
 *
 * This value is valid for these request in onRequestFinish when the
 * error code is MEGAErrorTypeApiOk:
 * - [MEGASdk getAccountDetails] - Details of the MEGA account
 *
 */
@property (readonly, nonatomic) MEGAAcountDetails *megaAcountDetails;

/**
 * @brief Available pricing plans to upgrade a MEGA account
 *
 * This value is valid for these request in onRequestFinish when the
 * error code is MEGAErrorTypeApiOk:
 * - [MEGASdk pricing] - Returns the available pricing plans
 *
 */
@property (readonly, nonatomic) MEGAPricing *pricing;

/**
 * @brief Creates a copy of this MEGARequest object
 *
 * The resulting object is fully independent of the source MEGARequest,
 * it contains a copy of all internal attributes, so it will be valid after
 * the original object is deleted.
 *
 * You are the owner of the returned object
 *
 * @return Copy of the MEGARequest object
 */
- (instancetype)clone;

@end
